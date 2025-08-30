#pragma once

#pragma once

namespace keycode
{
	enum Keys : int
	{
		MOUSELBUTTON = 0x01,
		MOUSERBUTTON = 0x02,
		CANCEL = 0x03,
		MBUTTON = 0x04,

		MOUSEXBUTTON1 = 0x05,
		MOUSEXBUTTON2 = 0x06,

		BACK = 0x08,
		TAB = 0x09,

		CLEAR = 0x0C,
		RETURN = 0x0D,

		SHIFT = 0x10,
		CONTROL = 0x11,
		MENU = 0x12,
		PAUSE = 0x13,
		CAPITAL = 0x14,

		KANA = 0x15,
		HANGEUL = 0x15,  /* old name - should be here for compatibility */
		HANGUL = 0x15,
		JUNJA = 0x17,
		FINAL = 0x18,
		HANJA = 0x19,
		KANJI = 0x19,

		ESCAPE = 0x1B,

		CONVERT = 0x1C,
		NONCONVERT = 0x1D,
		ACCEPT = 0x1E,
		MODECHANGE = 0x1F,

		SPACE = 0x20,
		PRIOR = 0x21, //page up
		NEXT = 0x22, //page down
		END = 0x23,
		HOME = 0x24,
		LEFT = 0x25,
		UP = 0x26,
		RIGHT = 0x27,
		DOWN = 0x28,
		SELECT = 0x29,
		PRINT = 0x2A,
		EXECUTE = 0x2B,
		SNAPSHOT = 0x2C,
		INSERT = 0x2D,
		DELETE_BUTTON = 0x2E,
		HELP = 0x2F,
		A = 0x41,
		B = 0x42,
		C = 0x43,
		D = 0x44,
		E = 0x45,
		F = 0x46,
		G = 0x47,
		H = 0x48,
		I = 0x49,
		J = 0x4A,
		K = 0x4B,
		L = 0x4C,
		M = 0x4D,
		N = 0x4E,
		O = 0x4F,
		P = 0x50,
		Q = 0x51,
		R = 0x52,
		S = 0x53,
		T = 0x54,
		U = 0x55,
		V = 0x56,
		W = 0x57,
		X = 0x58,
		Y = 0x59,
		Z = 0x5A,
		//
		LWIN = 0x5B,
		RWIN = 0x5C,
		APPS = 0x5D,

		SLEEP = 0x5F,

		NUMPAD0 = 0x60,
		NUMPAD1 = 0x61,
		NUMPAD2 = 0x62,
		NUMPAD3 = 0x63,
		NUMPAD4 = 0x64,
		NUMPAD5 = 0x65,
		NUMPAD6 = 0x66,
		NUMPAD7 = 0x67,
		NUMPAD8 = 0x68,
		NUMPAD9 = 0x69,
		MULTIPLY = 0x6A,
		ADD = 0x6B,
		SEPARATOR = 0x6C,
		SUBTRACT = 0x6D,
		DECIMAL = 0x6E,
		DIVIDE = 0x6F,
		F1 = 0x70,
		F2 = 0x71,
		F3 = 0x72,
		F4 = 0x73,
		F5 = 0x74,
		F6 = 0x75,
		F7 = 0x76,
		F8 = 0x77,
		F9 = 0x78,
		F10 = 0x79,
		F11 = 0x7A,
		F12 = 0x7B,
		F13 = 0x7C,
		F14 = 0x7D,
		F15 = 0x7E,
		F16 = 0x7F,
		F17 = 0x80,
		F18 = 0x81,
		F19 = 0x82,
		F20 = 0x83,
		F21 = 0x84,
		F22 = 0x85,
		F23 = 0x86,
		F24 = 0x87,

		NUMLOCK = 0x90,
		SCROLL = 0x91,

		OEM_NEC_EQUAL = 0x92,   // '=' key on numpad

		OEM_FJ_JISHO = 0x92,   // 'Dictionary' key
		OEM_FJ_MASSHOU = 0x93,   // 'Unregister word' key
		OEM_FJ_TOUROKU = 0x94,   // 'Register word' key
		OEM_FJ_LOYA = 0x95,   // 'Left OYAYUBI' key
		OEM_FJ_ROYA = 0x96,   // 'Right OYAYUBI' key

		LSHIFT = 0xA0,
		RSHIFT = 0xA1,
		LCONTROL = 0xA2,
		RCONTROL = 0xA3,
		LMENU = 0xA4,
		RMENU = 0xA5,

		BROWSER_BACK = 0xA6,
		BROWSER_FORWARD = 0xA7,
		BROWSER_REFRESH = 0xA8,
		BROWSER_STOP = 0xA9,
		BROWSER_SEARCH = 0xAA,
		BROWSER_FAVORITES = 0xAB,
		BROWSER_HOME = 0xAC,

		VOLUME_MUTE = 0xAD,
		VOLUME_DOWN = 0xAE,
		VOLUME_UP = 0xAF,
		MEDIA_NEXT_TRACK = 0xB0,
		MEDIA_PREV_TRACK = 0xB1,
		MEDIA_STOP = 0xB2,
		MEDIA_PLAY_PAUSE = 0xB3,
		LAUNCH_MAIL = 0xB4,
		LAUNCH_MEDIA_SELECT = 0xB5,
		LAUNCH_APP1 = 0xB6,
		LAUNCH_APP2 = 0xB7,

		OEM_1 = 0xBA,   // ';:' for US
		OEM_PLUS = 0xBB,   // '+' any country
		OEM_COMMA = 0xBC,   // ',' any country
		OEM_MINUS = 0xBD,   // '-' any country
		OEM_PERIOD = 0xBE,   // '.' any country
		OEM_2 = 0xBF,   // '/?' for US
		OEM_3 = 0xC0,   // '`~' for US

		GAMEPAD_A = 0xC3, // reserved
		GAMEPAD_B = 0xC4, // reserved
		GAMEPAD_X = 0xC5, // reserved
		GAMEPAD_Y = 0xC6, // reserved
		GAMEPAD_RIGHT_SHOULDER = 0xC7, // reserved
		GAMEPAD_LEFT_SHOULDER = 0xC8, // reserved
		GAMEPAD_LEFT_TRIGGER = 0xC9, // reserved
		GAMEPAD_RIGHT_TRIGGER = 0xCA, // reserved
		GAMEPAD_DPAD_UP = 0xCB, // reserved
		GAMEPAD_DPAD_DOWN = 0xCC, // reserved
		GAMEPAD_DPAD_LEFT = 0xCD, // reserved
		GAMEPAD_DPAD_RIGHT = 0xCE, // reserved
		GAMEPAD_MENU = 0xCF, // reserved
		GAMEPAD_VIEW = 0xD0, // reserved
		GAMEPAD_LEFT_THUMBSTICK_BUTTON = 0xD1, // reserved
		GAMEPAD_RIGHT_THUMBSTICK_BUTTON = 0xD2, // reserved
		GAMEPAD_LEFT_THUMBSTICK_UP = 0xD3, // reserved
		GAMEPAD_LEFT_THUMBSTICK_DOWN = 0xD4, // reserved
		GAMEPAD_LEFT_THUMBSTICK_RIGHT = 0xD5, // reserved
		GAMEPAD_LEFT_THUMBSTICK_LEFT = 0xD6, // reserved
		GAMEPAD_RIGHT_THUMBSTICK_UP = 0xD7, // reserved
		GAMEPAD_RIGHT_THUMBSTICK_DOWN = 0xD8, // reserved
		GAMEPAD_RIGHT_THUMBSTICK_RIGHT = 0xD9, // reserved
		GAMEPAD_RIGHT_THUMBSTICK_LEFT = 0xDA, // reserved

		OEM_4 = 0xDB,  //  '[{' for US
		OEM_5 = 0xDC,  //  '\|' for US
		OEM_6 = 0xDD,  //  ']}' for US
		OEM_7 = 0xDE,  //  ''"' for US
		OEM_8 = 0xDF,

		OEM_AX = 0xE1,  //  'AX' key on Japanese AX kbd
		OEM_102 = 0xE2,  //  "<>" or "\|" on RT 102-key kbd.
		ICO_HELP = 0xE3,  //  Help key on ICO
		ICO_00 = 0xE4,  //  00 key on ICO

		PROCESSKEY = 0xE5,

		ICO_CLEAR = 0xE6,

		PACKET = 0xE7,

		OEM_RESET = 0xE9,
		OEM_JUMP = 0xEA,
		OEM_PA1 = 0xEB,
		OEM_PA2 = 0xEC,
		OEM_PA3 = 0xED,
		OEM_WSCTRL = 0xEE,
		OEM_CUSEL = 0xEF,
		OEM_ATTN = 0xF0,
		OEM_FINISH = 0xF1,
		OEM_COPY = 0xF2,
		OEM_AUTO = 0xF3,
		OEM_ENLW = 0xF4,
		OEM_BACKTAB = 0xF5,

		ATTN = 0xF6,
		CRSEL = 0xF7,
		EXSEL = 0xF8,
		EREOF = 0xF9,
		PLAY = 0xFA,
		ZOOM = 0xFB,
		NONAME = 0xFC,
		PA1 = 0xFD,
		OEM_CLEAR = 0xFE
	};
}
