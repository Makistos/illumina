/*

Base addresses & interrupts
---------------------------

Normally, the following list is correct:

		Port     Base address    Int #  Int level

		COM1         0x3F8        0xC      4
		COM2         0x2F8        0xB      3
		COM3         0x3E8        0xC      4
		COM4         0x2E8        0xB      3

	Format of BIOS Data Segment at segment 40h:
	Offset Size Description
	 00h   WORD Base I/O address of 1st serial I/O port, zero if none
	 02h   WORD Base I/O address of 2nd serial I/O port, zero if none
	 04h   WORD Base I/O address of 3rd serial I/O port, zero if none
	 06h   WORD Base I/O address of 4th serial I/O port, zero if none

Registers
=========

COM1 COM2 COM3 COM4 Offs. DLAB  Register
------------------------------------------------------------------------------
3F8h 2F8h 3E8h 2E8h  +0     0   RBR  Receive Buffer Register (read only) or
																THR  Transmitter Holding Register (write only)
3F9h 2F9h 3E9h 2E9h  +1     0   IER  Interrupt Enable Register
3F8h 2F8h 3E8h 2E8h  +0     1   DL   Divisor Latch (LSB)  These registers can
3F9h 2F9h 3E9h 2E9h  +1     1   DL   Divisor Latch (MSB)  be accessed as word
3FAh 2FAh 3EAh 2EAh  +2     x   IIR  Interrupt Identification Register (r/o) or
																FCR  FIFO Control Register (w/o, 16550+ only)
3FBh 2FBh 3EBh 2EBh  +3     x   LCR  Line Control Register
3FCh 2FCh 3ECh 2ECh  +4     x   MCR  Modem Control Register
3FDh 2FDh 3EDh 2EDh  +5     x   LSR  Line Status Register
3FEh 2FEh 3EEh 2EEh  +6     x   MSR  Modem Status Register
3FFh 2FFh 3EFh 2EFh  +7     x   SCR  Scratch Register (16450+ and some 8250s,
																		 special use with some boards)

Programming
===========

int detect_UART(unsigned baseaddr)
{
	 // this function returns 0 if no UART is installed.
	 // 1: 8250, 2: 16450 or 8250 with scratch reg., 3: 16550, 4: 16550A
	 int x;
	 // first step: see if the LCR is there
	 outp(baseaddr+3,0x1b);
	 if (inp(baseaddr+3)!=0x1b) return 0;
	 outp(baseaddr+3,0x3);
	 if (inp(baseaddr+3)!=0x3) return 0;
	 // next thing to do is look for the scratch register
	 outp(baseaddr+7,0x55);
	 if (inp(baseaddr+7)!=0x55) return 1;
	 outp(baseaddr+7,0xAA);
	 if (inp(baseaddr+7)!=0xAA) return 1;
	 // then check if there's a FIFO
	 outp(baseaddr+2,1);
	 x=inp(baseaddr+2);
	 // some old-fashioned software relies on this!
	 outp(baseaddr+2,0x0);
	 if ((x&0x80)==0) return 2;
	 if ((x&0x40)==0) return 3;
	 return 4;
}

int detect_IRQ(unsigned base)
{
	// returns: -1 if no intlevel found, or intlevel 0-15
	char ier,mcr,imrm,imrs,maskm,masks,irqm,irqs;

	_asm cli;            // disable all CPU interrupts
	ier = inp(base+1);   // read IER
	outp(base+1,0);      // disable all UART ints
	while ((inp(base+5)&0x20)==0);  // wait for the THR to be empty
	mcr = inp(base+4);   // read MCR
	outp(base+4,0x0F);   // connect UART to irq line
	imrm = inp(0x21);    // read contents of master ICU mask register
	imrs = inp(0xA1);    // read contents of slave ICU mask register
	outp(0x20,0x0A);     // next read access to 0x20 reads out IRR
	outp(0xA0,0x0A);     // next read access to 0xA0 reads out IRR
	outp(base+1,2);      // lets generate interrupts...
	maskm = inp(0x20);   // this clears all bits except for the one
	masks = inp(0xA0);   // that corresponds to the int
	outp(base+1,0);      // drop the int line
	maskm &= ~inp(0x20); // this clears all bits except for the one
	masks &= ~inp(0xA0); // that corresponds to the int
	outp(base+1,2);      // and raise it again just to be sure...
	maskm &= inp(0x20);  // this clears all bits except for the one
	masks &= inp(0xA0);  // that corresponds to the int
	outp(0x21,~maskm);   // now let us unmask this interrupt only
	outp(0xA1,~masks);
	outp(0x20,0x0C);     // enter polled mode
	outp(0xA0,0x0C);
	irqs = inp(0xA0);    // and accept the interrupt
	irqm = inp(0x20);
	inp(base+2);         // reset transmitter interrupt in UART
	outp(base+4,mcr);    // restore old value of MCR
	outp(base+1,ier);    // restore old value of IER
	if (masks) outp(0xA0,0x20);  // send an EOI to slave
	if (maskm) outp(0x20,0x20);  // send an EOI to master
	outp(0x21,imrm);     // restore old mask register contents
	outp(0xA1,imrs);
	_asm sti;
	if (irqs&0x80)       // slave interrupt occured
	return (irqs&0x07)+8;
	if (irqm&0x80)       // master interrupt occured
	return irqm&0x07;
	return -1;
}

Now the non-interrupt version of TX and RX.


	UART_BASEADDR   the base address of the UART
	UART_BAUDRATE   the divisor value (eg. 12 for 9600 bps)
	UART_LCRVAL     the value to be written to the LCR (eg. 0x1b for 8e1)
	UART_FCRVAL     the value to be written to the FCR. Bit 0, 1 and 2 set,
									bits 6 & 7 according to trigger level wished (see above).
									0x87 is a good value, 0x7 establishes compatibility
									(except that there are some bits to be masked in the IIR).

UART_init proc near
	push ax  ; we are 'clean guys'
	push dx
	mov  dx,UART_BASEADDR+3  ; LCR
	mov  al,80h  ; set DLAB
	out  dx,al
	mov  dx,UART_BASEADDR    ; divisor
	mov  ax,UART_BAUDRATE
	out  dx,ax
	mov  dx,UART_BASEADDR+3  ; LCR
	mov  al,UART_LCRVAL  ; params
	out  dx,al
	mov  dx,UART_BASEADDR+4  ; MCR
	xor  ax,ax  ; clear loopback
	out  dx,al
	;***
	pop  dx
	pop  ax
	ret
UART_init endp

void UART_init()
{
	 outp(UART_BASEADDR+3,0x80);
	 outpw(UART_BASEADDR,UART_BAUDRATE);
	 outp(UART_BASEADDR+3,UART_LCRVAL);
	 outp(UART_BASEADDR+4,0);
	 //***
}

UART_send proc near
	; character to be sent in AL
	push dx
	push ax
	mov  dx,UART_BASEADDR+5
us_wait:
	in   al,dx  ; wait until we are allowed to write a byte to the THR
	test al,20h
	jz   us_wait
	pop  ax
	mov  dx,UART_BASEADDR
	out  dx,al  ; then write the byte
	pop  dx
	ret
UART_send endp

void UART_send(char character)
{
	 while ((inp(UART_BASEADDR+5)&0x20)==0);
	 outp(UART_BASEADDR,(int)character);
}

UART_send_string proc near
	; DS:SI contains a pointer to the string to be sent.
	push si
	push ax
	push dx
	cld  ; we want to read the string in its correct order
uss_loop:
	lodsb
	or   al,al  ; last character sent?
	jz   uss_end
	;*1*
	mov  dx,UART_BASEADDR+5
	push ax
uss_wait:
	in   al,dx
	test al,20h
	jz   uss_wait
	mov  dx,UART_BASEADDR
	pop  ax
	out  dx,al
	;*2*
	jmp  uss_loop
uss_end:
	pop  dx
	pop  ax
	pop  si
	ret
UART_send_string endp

void UART_send_string(char *string)
{
	 int i;
	 for (i=0; string[i]!=0; i++)
			{
			//*1*
			while ((inp(UART_BASEADDR+5)&0x20)==0);
			outp(UART_BASEADDR,(int)string[i]);
			//*2*
			}
}


UART_get_char proc near
	push dx
	mov  dx,UART_BASEADDR+5
	in   al,dx
	xchg al,ah
	and  ax,9f00h
	test al,1
	jz   ugc_nochar
	mov  dx,UART_BASEADDR
	in   al,dx
ugc_nochar:
	pop  dx
	ret
UART_get_char endp

unsigned UART_get_char()
{
	 unsigned x;
	 x = (inp(UART_BASEADDR+5) & 0x9f) << 8;
	 if (x&0x100) x|=((unsigned)inp(UART_BASEADDR))&0xff;
	 return x;
}

DOS_print macro pointer
	; prints a string in the code segment
	push ax
	push ds
	push dx
	push cs
	pop  ds
	mov  dx,pointer
	mov  ah,9
	int  21h
	pop  dx
	pop  ds
	pop  ax
endm

UART_watch_rxd proc near
uwr_loop:
	; check if keyboard hit; we want a possibility to break the loop
	mov  ah,1  ; Beware! Don't call INT 16h with high transmission
	int  16h   ; rates, it won't work!
	jnz  uwr_exit
	call UART_get_char
	or   ax,ax
	jz   uwr_loop
	test ah,1  ; is there a character in AL?
	jz   uwr_nodata
	push ax    ; yes, print it
	mov  dl,al ;\
	mov  ah,2  ; better use this for high rates: mov ah,0eh
	int  21h   ;/                                int 10h
	pop  ax
uwr_nodata:
	test ah,0eh ; any error at all?
	jz   uwr_loop  ; this speeds up things since errors should be rare
	test ah,2  ; overrun error?
	jz   uwr_noover
	DOS_print overrun_text
uwr_noover:
	test ah,4  ; parity error?
	jz   uwr_nopar
	DOS_print parity_text
uwr_nopar:
	test ah,8  ; framing error?
	jz   uwr_loop
	DOS_print framing_text
	jmp  uwr_loop
uwr_exit:
	ret
overrun_text    db "*** Overrun Error ***$"
parity_text     db "*** Parity Error ***$"
framing_text    db "*** Framing Error ***$"
UART_watch_rxd endp

void UART_watch_rxd()
{
	 union {
			unsigned val;
			char character;
			} x;
	 while (!kbhit()) {
			x.val=UART_get_char();
			if (!x.val) continue;  // nothing? Continue
			if (x.val&0x100) putc(x.character);  // character? Print it
			if (!(x.val&0xe00)) continue;  // any error condidion? No, continue
			if (x.val&0x200) printf("*** Overrun Error ***");
			if (x.val&0x400) printf("*** Parity Error ***");
			if (x.val&0x800) printf("*** Framing Error ***");
			}
}

terminal proc near
ter_loop:
	call UART_watch_rxd  ; watch line until a key is pressed
	xor  ax,ax  ; get that key from the keyboard buffer
	int  16h
	cmp  al,27  ; is it ESC?
	jz   ter_end  ; yes, then end this function
	call UART_send  ; send the character typed if it's not ESC
	jmp  ter_loop  ; don't forget to check if data comes in
ter_end:
	ret
terminal endp

void terminal()
{
	 int key;
	 while (1)
			{
			UART_watch_rxd();
			key=getche();
			if (key==27) break;
			UART_send((char)key);
			}
}


main proc near
	call UART_init
	call terminal
	mov  ax,4c00h
	int  21h
main endp
code ends
stack segment stack 'stack'
	dw 128 dup (?)
stack ends
end main

void main()
{
	 UART_init();
	 terminal();
}


Interrupt-based version:

UART_INT      EQU 0Ch  ; for COM2 / COM4 use 0bh
UART_ONMASK   EQU 11101111b  ; for COM2 / COM4 use 11110111b
UART_OFFMASK  EQU NOT UART ONMASK
UART_IERVAL   EQU ?   ; replace ? by any value between 0h and 0fh
											; (dependent on which ints you want)
											; DON'T SET bit 1 now! (not with this kind of service
											; routine, that is)
UART_OLDVEC   DD  ?

initialize_UART_interrupt proc near
	push ds
	push es  ; first thing is to store the old interrupt
	push bx  ; vector
	mov  ax,3500h+UART_INT
	int  21h
	mov  word ptr UART_OLDVEC,bx
	mov  word ptr UART_OLDVEC+2,es
	pop  bx
	pop  es
	push cs  ; build a pointer in DS:DX
	pop  ds
	lea  dx,interrupt_service_routine
	mov  ax,2500h+UART_INT
	int  21h ; and ask DOS to set this pointer as the new interrrupt vector
  pop  ds
  mov  dx,UART_BASEADDR+4  ; MCR
  in   al,dx
  or   al,8  ; set OUT2 bit to enable interrupts
  out  dx,al
  mov  dx,UART_BASEADDR+1  ; IER
  mov  al,UART_IERVAL  ; enable the interrupts we want
  out  dx,al
  in   al,21h  ; last thing to do is unmask the int in the ICU
  and  al,UART_ONMASK
  out  21h,al
  sti  ; and free interrupts if they have been disabled
  ret
initialize_UART_interrupt endp

deinitialize_UART_interrupt proc near
  push ds
  lds  dx,UART_OLDVEC
  mov  ax,2500h+UART_INT
  int  21h
  pop  ds
  in   al,21h  ; mask the UART interrupt
  or   al,UART_OFFMASK
  out  21h,al
  mov  dx,UART_BASEADDR+1
  xor  al,al
  out  dx,al   ; clear all interrupt enable bits
  mov  dx,UART_BASEADDR+4
  out  dx,al   ; and disconnect the UART from the ICU
  ret
deinitialize_UART_interrupt endp

interupt_service_routine proc far  ; define as near if you want to link .COM
	;*1*                             ; it doesn't matter anyway since IRET is
	push ax                          ; always a FAR command
	push cx
	push dx
	push bx
	push sp
	push bp
	push si
	push di
	;*2*   replace the part between *1* and *2* by pusha on an 80186+ system
	push ds
	push es
	mov  al,20h    ; remember: first thing to do in interrupt routines is tell
	out  20h,al    ; the ICU about the service being done. This avoids lock-up
int_loop:
	mov  dx,UART_BASEADDR+2  ; IIR
	in   al,dx  ; check IIR info
	test al,1
	jnz  int_end
	and  ax,6  ; we're interested in bit 1 & 2 (see data sheet info)
	mov  si,ax ; this is already an index! Well-devised, huh?
	call word ptr cs:int_servicetab[si]  ; ensure a near call is used...
	jmp  int_loop
int_end:
	pop  es
	pop  ds
	;*3*
	pop  di
	pop  si
	pop  bp
	pop  sp
	pop  bx
	pop  dx
	pop  cx
	pop  ax
	;*4*   *3* - *4* can be replaced by popa on an 80186+ based system
	iret
interupt_service_routine endp

int_servicetab    DW int_modem, int_tx, int_rx, int_status

int_modem proc near
	mov  dx,UART_BASE+6  ; MSR
	in   al,dx
	; do with the info what you like; probably just ignore it...
	; but YOU MUST READ THE MSR or you'll lock up the interrupt!
	ret
int_modem endp

int_tx proc near
	; get next byte of data from a buffer or something
	; (remember to set the segment registers correctly!)
	; and write it to the THR (offset 0)
	; if no more data is to be sent, disable the THRE interrupt
	; If the FIFOs are switched on (and you've made sure it's a 16550A!), you
	; can write up to 16 characters

	; end of data to be sent?
	; no, jump to end_int_tx
	mov  dx,UART_BASEADDR+1
	in   al,dx
	and  al,00001101b
	out  dx,al
end_int_tx:
	ret
int_tx endp

int_rx proc near
	mov  dx,UART_BASEADDR
	in   al,dx
	; do with the character what you like (best write it to a
	; FIFO buffer [not the one of the 16550A, silly! :)])
	; the following lines speed up FIFO mode operation
	mov  dx,UART_BASEADDR+5
	in   al,dx
	test al,1
	jnz  int_rx
	; these lines are a cure for the well-known problem of TX interrupt
	; lock-ups when receiving and transmitting at the same time
	test al,40h
	je   dont_unlock
	call int_tx
dont_unlock:
	ret
int_rx endp

int_status proc near
	mov  dx,UART_BASEADDR+5
	in   al,dx
	; do what you like. It's just important to read the LSR
	ret
int_status endp


	; copy data to buffer

	mov  dx,UART_BASEADDR+1  ; IER
	in   al,dx
	or   al,2  ; set bit 1
	out  dx,al
	nop
	nop  ; give the UART some time to kick the interrupt...
	nop
	mov  dx,UART_BASEADDR+5  ; LSR
	cli  ; make sure no interrupts get in-between if not already running
	in   al,dx
	test al,40h  ; is there a transmission running?
	jz   dont_crank  ; yes, so don't mess it up
	call int_tx  ; no, crank it up
	sti
dont_crank:


	; just a small terminal program using interrupts.
	; It's quite dumb: it uses the BIOS for screen output
	; and keyboard input
	; assemble and link as .EXE (just type ml name)
	; If you have a 16550 (not a 16550A), you may lose
	; characters since the fifos are turned on (see "Known problems
	; with several chips")
	; If your BIOS locks the interrupts while scrolling (some do),
	; you may encounter data loss at high rates.

model small
dosseg

INTNUM      equ 0Ch          ; COM1; COM2: 0Bh
OFFMASK     equ 00010000b    ; COM1; COM2: 00001000b
ONMASK      equ not OFFMASK
UART_BASE   equ 3F8h         ; COM1; COM2: 2F8h
UART_RATE   equ 12           ; 9600 bps, see table in this file
UART_PARAMS equ 00000011b    ; 8n1, see tables
RXFIFOSIZE  equ 8096         ; set this to your needs
TXFIFOSIZE  equ 8096         ; dito.
														 ; the fifos must be large on slow computers
														 ; and can be small on fast ones
														 ; These have nothing to do with the 16550A's
														 ; built-in FIFOs!

.data
long_text  db  0dh
		db  "This is a very long test string. It serves the purpose of",0dh
		db  "demonstrating that our interrupt-driven routines are capable",0dh
		db  "of coping with pressure situations like the one we provoke",0dh
		db  "by sending large bunches of characters in each direction at",0dh
		db  "the same time. Run this test by pressing F1 at a low data",0dh
		db  "rate and a high data rate to see why serial transmission and",0dh
		db  "reception should be programmed interrupt-driven. You won't lose",0dh
		db  "a single character as long as you don't overload the fifos, no",0dh
		db  "matter how hard you try!",0dh,0

ds_dgroup  macro
	mov  ax,DGROUP
	mov  ds,ax
	assume  ds:DGROUP
endm

ds_text  macro
	push  cs
	pop   ds
	assume  ds:_TEXT
endm

rx_checkwrap  macro
	local rx_nowrap
	cmp  si,offset rxfifo+RXFIFOSIZE
	jb  rx_nowrap
	lea  si,rxfifo
rx_nowrap:
endm

tx_checkwrap  macro
  local tx_nowrap
  cmp  si,offset txfifo+TXFIFOSIZE
  jb  tx_nowrap
  lea  si,txfifo
tx_nowrap:
endm

.stack 256

.data?
old_intptr  dd  ?
rxhead      dw  ?
rxtail      dw  ?
txhead      dw  ?
txtail      dw  ?
bitxfifo    dw  1  ; size of built-in TX fifo (1 if no fifo)
rxfifo      db  RXFIFOSIZE dup (?)
txfifo      db  TXFIFOSIZE dup (?)

.code
start  proc far
  call  install_interrupt_handler
  call  clear_fifos
  call  clear_screen
  call  init_UART
continue:
  call  read_RX_fifo
  call  read_keyboard
  jnc  continue
  call  clean_up
  mov  ax,4c00h
  int  21h  ; return to DOS
start  endp

interrupt_handler  proc far
  assume  ds:nothing,es:nothing,ss:nothing,cs:_text
  push  ax
  push  cx
  push  dx  ; first save the regs we need to change
  push  ds
  push  si
  mov  al,20h  ; acknowledge interrupt
  out  20h,al

ih_continue:
  mov  dx,UART_BASE+2
  xor  ax,ax
  in  al,dx  ; get interrupt cause
  test  al,1  ; did the UART generate the int?
  jne  ih_sep  ; no, then it's somebody else's problem
  and  al,6  ; mask bits not needed
  mov  si,ax  ; make a pointer out of it
  call  interrupt_table[si]  ; serve this int
	jmp  ih_continue  ; and look for more things to be done
ih_sep:
  pop  si
  pop  ds
  pop  dx  ; restore regs
  pop  cx
  pop  ax
  iret
interrupt_table  dw  int_modem,int_tx,int_rx,int_status
interrupt_handler  endp

int_modem  proc near
  ; just clear modem status, we are not interested in it
  mov  dx,UART_BASE+6
  in  al,dx
  ret
int_modem  endp

int_tx  proc near
  ds_dgroup
  ; check if there's something to be sent
  mov  si,txtail
  mov  cx,bitxfifo
itx_more:
  cmp  si,txhead
  je  itx_nothing
  cld
  lodsb
  mov  dx,UART_BASE
  out  dx,al  ; write it to the THR
  ; check for wrap-around in our fifo
  tx_checkwrap
  ; send as much bytes as the chip can take when available
  loop itx_more
  jmp  itx_dontstop
itx_nothing:
  ; no more data in the fifo, so inhibit TX interrupts
  mov  dx,UART_BASE+1
  mov  al,00000001b
  out  dx,al
itx_dontstop:
  mov  txtail,si
  ret
int_tx  endp

int_rx  proc near
  ds_dgroup
  mov  si,rxhead
irx_more:
  mov  dx,UART_BASE
  in  al,dx
  mov  byte ptr [si],al
  inc  si
  ; check for wrap-around
  rx_checkwrap
  ; see if there are more bytes to be read
  mov  dx,UART_BASE+5
  in  al,dx
  test  al,1
  jne  irx_more
  mov  rxhead,si
  test  al,40h  ; Sometimes when sending and receiving at the
  jne  int_tx   ; same time, TX ints get lost. This is a cure.
  ret
int_rx  endp

int_status  proc near
  ; just clear the status ("this trivial task is left as an exercise
  ; to the student")
  mov  dx,UART_BASE+5
  in  al,dx
  ret
int_status  endp

read_RX_fifo  proc near
  ; see if there are bytes to be read from the fifo
  ; we read a maximum of 16 bytes, then return in order
  ; not to break keyboard control
  ds_dgroup
  cld
	mov  cx,16
  mov  si,rxtail
rx_more:
  cmp  si,rxhead
  je  rx_nodata
  lodsb
  call  output_char
  ; check for wrap-around
  rx_checkwrap
  loop  rx_more
rx_nodata:
  mov  rxtail,si
  ret
read_RX_fifo  endp

read_keyboard  proc near
  ds_dgroup
  ; check for keys pressed
  mov  ah,1
  int  16h
  je  rk_nokey
  xor  ax,ax
  int  16h
  cmp  ax,2d18h  ; is it Ctrl-X?
  stc
  je  rk_ctrlx
  cmp  ax,3b00h  ; is it F1?
  jne  rk_nf1
  lea  si,long_text  ; send a very long test string
  call  send_string
  jmp  rk_nokey
rk_nf1:
  ; echo the character to the screen
  call  output_char

  call  send_char
rk_nokey:
  clc
rk_ctrlx:
  ret
read_keyboard  endp


install_interrupt_handler  proc near
  ds_dgroup
	; install interrupt handler first
  mov  ax,3500h+INTNUM
  int  21h
  mov  word ptr old_intptr,bx
  mov  word ptr old_intptr+2,es
  mov  ax,2500h+INTNUM
  ds_text
  lea  dx,interrupt_handler
  int  21h
  ret
install_interrupt_handler  endp

clear_fifos  proc near
  ds_dgroup
  ; clear fifos (not those in the 16550A, but ours)
  lea  ax,rxfifo
  mov  rxhead,ax
  mov  rxtail,ax
  lea  ax,txfifo
  mov  txhead,ax
  mov  txtail,ax
  ret
clear_fifos  endp

init_UART  proc near
  ; initialize the UART
  mov  dx,UART_BASE+3
  mov  al,80h
  out  dx,al  ; make DL register accessible
  mov  dx,UART_BASE
  mov  ax,UART_RATE
  out  dx,ax  ; write bps rate divisor
  mov  dx,UART_BASE+3
  mov  al,UART_PARAMS
  out  dx,al  ; write parameters
  
  ; is it a 16550A?
  mov  dx,UART_BASE+2
  in   al,dx
  and  al,11000000b
  cmp  al,11000000b
  jne  iu_nofifos
  mov  bitxfifo,16
  mov  dx,UART_BASE+2
  mov  al,11000111b
	out  dx,al  ; clear and enable the fifos if they exist
iu_nofifos:
  mov  dx,UART_BASE+1
  mov  al,00000001b  ; allow RX interrupts
  out  dx,al
  mov  dx,UART_BASE
  in  al,dx  ; clear receiver
  mov  dx,UART_BASE+5
  in  al,dx  ; clear line status
  inc  dx
	in  al,dx  ; clear modem status
  ; free interrupt in the ICU
  in  al,21h
  and  al,ONMASK
  out  21h,al
  ; and enable ints from the UART
  mov  dx,UART_BASE+4
  mov  al,00001000b
  out  dx,al
  ret
init_UART  endp

clear_screen  proc near
  mov  ah,0fh  ; allow all kinds of video adapters to be used
  int  10h
  cmp  al,7
  je  cs_1
  mov  al,3
cs_1:
  xor  ah,ah
  int  10h
  ret
clear_screen  endp

clean_up  proc near
  ds_dgroup
  ; lock int in the ICU
  in  al,21h
  or  al,OFFMASK
  out  21h,al
  xor  ax,ax
  mov  dx,UART_BASE+4  ; disconnect the UART from the int line
  out  dx,al
  mov  dx,UART_BASE+1  ; disable UART ints
  out  dx,al
	mov  dx,UART_BASE+2  ; disable the fifos (old software relies on it)
  out  dx,al
  ; restore int vector
  lds  dx,old_intptr
  mov  ax,2500h+INTNUM
  int  21h
  ret
clean_up  endp

output_char  proc near
	push  si
	push  ax
oc_cr:
	push  ax
	mov  ah,0eh  ; output character using BIOS TTY
	int  10h     ; it's your task to improve this
	pop  ax
	cmp  al,0dh  ; add LF after CR; change it if you don't like it
	mov  al,0ah
	je  oc_cr
	pop  ax
	pop  si
	ret
output_char  endp

send_char proc near
	push  si
	push  ax
	ds_dgroup
	pop  ax
	mov  si,txhead
	mov  byte ptr [si],al
	inc  si
	; check for wrap-around
	tx_checkwrap
	mov  txhead,si
	; test if the interrupt is running at the moment
	mov  dx,UART_BASE+5
	in  al,dx
	test  al,40h
	je  sc_dontcrank
	; crank it up
	; note that this might not work with some very old 8250s
	mov  dx,UART_BASE+1
	mov  al,00000011b
	out  dx,al
sc_dontcrank:
	pop  si
	ret
send_char  endp

send_string  proc near
	; sends a null-terminated string pointed at by DS:SI
	ds_dgroup
	cld
ss_more:
	lodsb
	or  al,al
	je  ss_end
	call send_char
	jmp  ss_more
ss_end:
	ret
send_string  endp

end start

*/

