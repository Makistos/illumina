// Keyboard.h

const char
			KEY_ESC         = 0x01,
			KEY_F1          = 0x3B,
			KEY_F2          = 0x3C,
			KEY_F3          = 0x3D,
			KEY_F4          = 0x3E,
			KEY_F5          = 0x3F,
			KEY_F6          = 0x40,
			KEY_F7          = 0x41,
			KEY_F8          = 0x42,
			KEY_F9          = 0x43,
			KEY_F10         = 0x44,
			KEY_F11         = 0x57,
			KEY_F12         = 0x58,

			KEY_HALF        = 0x29,
			KEY_1           = 0x02,
			KEY_2           = 0x03,
			KEY_3           = 0x04,
			KEY_4           = 0x05,
			KEY_5           = 0x06,
			KEY_6           = 0x07,
			KEY_7           = 0x08,
			KEY_8           = 0x09,
			KEY_9           = 0x0A,
			KEY_0           = 0x0B,
			KEY_PLUS        = 0x0C,
			KEY_NOTE        = 0x0D,
			KEY_BKSPC       = 0x0E,

			KEY_TAB         = 0x0F,
			KEY_Q           = 0x10,
			KEY_W           = 0x11,
			KEY_E           = 0x12,
			KEY_R           = 0x13,
			KEY_T           = 0x14,
			KEY_Y           = 0x15,
			KEY_U           = 0x16,
			KEY_I           = 0x17,
			KEY_O           = 0x18,
			KEY_P           = 0x19,
			KEY_LEFTB       = 0x1A,
			KEY_RIGHTB      = 0x1B,
			KEY_ENTER       = 0x1C,

			KEY_CLOCK       = 0x3A,
			KEY_A           = 0x1E,
			KEY_S           = 0x1F,
			KEY_D           = 0x20,
			KEY_F           = 0x21,
			KEY_G           = 0x22,
			KEY_H           = 0x23,
			KEY_J           = 0x24,
			KEY_K           = 0x25,
			KEY_L           = 0x26,
			KEY_DBLDOT      = 0x27,
			// KEY_COLON ?
			KEY_DBLCOMMA    = 0x28,
			// KEY_SEMICOLON ?
			KEY_ASTERISK    = 0x2B,

			KEY_LSHIFT      = 0x1D,
			KEY_PIPE        = 0x56,
			KEY_Z           = 0x2C,
			KEY_X           = 0x2D,
			KEY_C           = 0x2E,
			KEY_V           = 0x2F,
			KEY_B           = 0x30,
			KEY_N           = 0x31,
			KEY_M           = 0x32,
			KEY_COMMA       = 0x33,
			KEY_DOT         = 0x34,
			KEY_MINUS       = 0x35,
			KEY_RSHIFT      = 0x36,

			KEY_CTRL        = 0x1D,
			KEY_ALT         = 0x38,
			KEY_SPACE       = 0x39,

			KEY_PRSCR       = 0x37,
			KEY_ALTPRSCR    = 0x54,
			KEY_SCRLOCK     = 0x46,
			KEY_PAUSE       = 0x45,
			KEY_BREAK       = 0x46,

			KEY_NLOCK       = 0x45,
			KEY_NDIV        = 0x35,
			KEY_NMULT       = 0x37,
			KEY_NMINUS      = 0x4A,
			KEY_HOME        = 0x47,
			KEY_UP          = 0x48,
			KEY_PGUP        = 0x49,
			KEY_NPLUS       = 0x4E,
			KEY_LEFT        = 0x4B,
			KEY_RIGHT       = 0x4D,
			KEY_END         = 0x4F,
			KEY_DOWN        = 0x50,
			KEY_PGDN        = 0x51,
			KEY_INS         = 0x52,
			KEY_DEL         = 0x53,

			KEY_N0          = 0x52,
			KEY_N1          = 0x4F,
			KEY_N2          = 0x50,
			KEY_N3          = 0x51,
			KEY_N4          = 0x4B,
			KEY_N5          = 0x4C,
			KEY_N6          = 0x4D,
			KEY_N7          = 0x47,
			KEY_N8          = 0x48,
			KEY_N9          = 0x49;

extern volatile char keyDown[128];
extern volatile char lastKey;
extern volatile char releasedKey;
extern volatile char keyHit;

void keyInit(void);
void keyDone(void);
char getKey(void);
char keyPressed(void);