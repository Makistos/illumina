#ifndef __keybrd_h__
#define __keybrd_h__


#include <conio.h>

#define GETKEY ((kbhit() ? getch() : 0))

/*****************************
 * Special keys
 *****************************/

#define	    KEY_ESC          27
#define			KEY_F1           1059
#define			KEY_F2           1060
#define			KEY_F3           1061
#define			KEY_F4           1062
#define			KEY_F5           1063
#define			KEY_F6           1064
#define			KEY_F7           1065
#define			KEY_F8           1066
#define			KEY_F9           1067
#define			KEY_F10          1068
#define			KEY_F11          1069
#define			KEY_F12          1070

#define			KEY_HALF         0x29
#define			KEY_0            48
#define			KEY_1            49
#define			KEY_2            50
#define			KEY_3            51
#define			KEY_4            52
#define			KEY_5            53
#define			KEY_6            54
#define			KEY_7            55
#define			KEY_8            56
#define			KEY_9            57
#define			KEY_PLUS         0x0C
#define			KEY_NOTE         0x0D
#define			KEY_BKSPC        0x0E

#define			KEY_TAB          0x0F
#define			KEY_A            65
#define			KEY_B            66
#define			KEY_C            67
#define			KEY_D            68
#define			KEY_E            69
#define			KEY_F            70
#define			KEY_G            71
#define			KEY_H            72
#define			KEY_I            73
#define			KEY_J            74
#define			KEY_K            75
#define			KEY_L            76
#define			KEY_M            77
#define			KEY_N            78
#define			KEY_O            79
#define			KEY_P            80
#define			KEY_Q            81
#define			KEY_R            82
#define			KEY_S            83
#define			KEY_T            84
#define			KEY_U            85
#define			KEY_V            86
#define			KEY_W            87
#define			KEY_X            88
#define			KEY_Y            89
#define			KEY_Z            90
#define			KEY_a            97
#define			KEY_b            98
#define			KEY_c            99
#define			KEY_d            100
#define			KEY_e            101
#define			KEY_f            102
#define			KEY_g            103
#define			KEY_h            104
#define			KEY_i            105
#define			KEY_j            106
#define			KEY_k            107
#define			KEY_l            108
#define			KEY_m            109
#define			KEY_n            110
#define			KEY_o            111
#define			KEY_p            112
#define			KEY_q            113
#define			KEY_r            114
#define			KEY_s            115
#define			KEY_t            116
#define			KEY_u            117
#define			KEY_v            118
#define			KEY_w            119
#define			KEY_x            120
#define			KEY_y            121
#define			KEY_z            122
#define			KEY_LEFTB        0x1A
#define			KEY_RIGHTB       0x1B
#define			KEY_ENTER        0x1C

#define			KEY_CLOCK        0x3A
#define			KEY_COLON        0x27
			/* KEY_COLON ? */
#define			KEY_SEMICOLON    0x28
			/* KEY_SEMICOLON ? */
#define			KEY_ASTERISK     0x2B

#define			KEY_LSHIFT       0x1D
#define			KEY_PIPE         0x56
#define			KEY_COMMA        0x33
#define			KEY_DOT          0x34

#define			KEY_MINUS        0x35
#define			KEY_RSHIFT       0x36

#define			KEY_CTRL         0x1D
#define			KEY_ALT          0x38
#define			KEY_SPACE        0x39

#define			KEY_PRSCR        0x37
#define			KEY_ALTPRSCR     0x54
#define			KEY_SCRLOCK      0x46
#define			KEY_PAUSE        0x45
#define			KEY_BREAK        0x46

#define			KEY_NLOCK        0x45
#define			KEY_NDIV         0x35
#define			KEY_NMULT        0x37
#define			KEY_NMINUS       0x4A
#define			KEY_HOME         0x47
#define			KEY_UP           0x48
#define			KEY_PGUP         0x49
#define			KEY_NPLUS        0x4E
#define			KEY_LEFT         0x4B
#define			KEY_RIGHT        0x4D
#define			KEY_END          0x4F
#define			KEY_DOWN         0x50
#define			KEY_PGDN         0x51
#define			KEY_INS          0x52
#define			KEY_DEL          0x53

#define			KEY_N0           0x52
#define			KEY_N1           0x4F
#define			KEY_N2           0x50
#define			KEY_N3           0x51
#define			KEY_N4           0x4B
#define			KEY_N5           0x4C
#define			KEY_N6           0x4D
#define			KEY_N7           0x47
#define			KEY_N8           0x48
#define			KEY_N9           0x49


/****************************
 * Functions
 ****************************/

/*
char getKey(void);
*/


#endif