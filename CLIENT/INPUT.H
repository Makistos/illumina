// INPUT.H

const int
			CMD_ESC         = 0x01,
			CMD_F1          = 0x3B,
			CMD_F2          = 0x3C,
			CMD_F3          = 0x3D,
			CMD_F4          = 0x3E,
			CMD_F5          = 0x3F,
			CMD_F6          = 0x40,
			CMD_F7          = 0x41,
			CMD_F8          = 0x42,
			CMD_F9          = 0x43,
			CMD_F10         = 0x44,
			CMD_F11         = 0x57,
			CMD_F12         = 0x58,

			CMD_HALF        = 0x29,
			CMD_1           = 0x02,
			CMD_2           = 0x03,
			CMD_3           = 0x04,
			CMD_4           = 0x05,
			CMD_5           = 0x06,
			CMD_6           = 0x07,
			CMD_7           = 0x08,
			CMD_8           = 0x09,
			CMD_9           = 0x0A,
			CMD_0           = 0x0B,
			CMD_PLUS        = 0x0C,
			CMD_NOTE        = 0x0D,
			CMD_BKSPC       = 0x0E,

			CMD_TAB         = 0x0F,
			CMD_Q           = 0x10,
			CMD_W           = 0x11,
			CMD_E           = 0x12,
			CMD_R           = 0x13,
			CMD_T           = 0x14,
			CMD_Y           = 0x15,
			CMD_U           = 0x16,
			CMD_I           = 0x17,
			CMD_O           = 0x18,
			CMD_P           = 0x19,
			CMD_LEFTB       = 0x1A,
			CMD_RIGHTB      = 0x1B,
			CMD_ENTER       = 0x1C,

			CMD_CLOCK       = 0x3A,
			CMD_A           = 0x1E,
			CMD_S           = 0x1F,
			CMD_D           = 0x20,
			CMD_F           = 0x21,
			CMD_G           = 0x22,
			CMD_H           = 0x23,
			CMD_J           = 0x24,
			CMD_K           = 0x25,
			CMD_L           = 0x26,
			CMD_DBLDOT      = 0x27,
			CMD_DBLCOMMA    = 0x28,
			CMD_ASTERISK    = 0x2B,

			CMD_LSHIFT      = 0x1D,
			CMD_PIPE        = 0x56,
			CMD_Z           = 0x2C,
			CMD_X           = 0x2D,
			CMD_C           = 0x2E,
			CMD_V           = 0x2F,
			CMD_B           = 0x30,
			CMD_N           = 0x31,
			CMD_M           = 0x32,
			CMD_COMMA       = 0x33,
			CMD_DOT         = 0x34,
			CMD_MINUS       = 0x35,
			CMD_RSHIFT      = 0x36,

			CMD_CTRL        = 0x1D,
			CMD_ALT         = 0x38,
			CMD_SPACE       = 0x39,

			CMD_PRSCR       = 0x37,
			CMD_ALTPRSCR    = 0x54,
			CMD_SCRLOCK     = 0x46,
			CMD_PAUSE       = 0x45,
			CMD_BREAK       = 0x46,

			CMD_NLOCK       = 0x45,
			CMD_NDIV        = 0x35,
			CMD_NMULT       = 0x37,
			CMD_NMINUS      = 0x4A,
			CMD_HOME        = 0x47,
			CMD_UP          = 0x48,
			CMD_PGUP        = 0x49,
			CMD_NPLUS       = 0x4E,
			CMD_LEFT        = 0x4B,
			CMD_RIGHT       = 0x4D,
			CMD_END         = 0x4F,
			CMD_DOWN        = 0x50,
			CMD_PGDN        = 0x51,
			CMD_INS         = 0x52,
			CMD_DEL         = 0x53,

			CMD_N0          = 0x52,
			CMD_N1          = 0x4F,
			CMD_N2          = 0x50,
			CMD_N3          = 0x51,
			CMD_N4          = 0x4B,
			CMD_N5          = 0x4C,
			CMD_N6          = 0x4D,
			CMD_N7          = 0x47,
			CMD_N8          = 0x48,
			CMD_N9          = 0x49;

extern volatile char ispressed[128];
extern int stick_x;
extern int stick_y;

void kbd_init(void);
void kbd_done(void);

void stick_range(int);
void stick_reset(void); 			// Max,min -> centerpoint
void stick_center(void);      // Joystick coordinates -> Center point
void stick_update(void);
