#pragma once

#pragma once

namespace ENGINE_NAMESPACE
{
	enum class MouseButton
	{
		LEFT = 0,
		RIGHT = 1,
		MIDDLE = 2,

		BACK_BUTTON = 3,
		FORWARD_BUTTON = 4,
	};

	enum class Keycode : int
	{
		ESCAPE = 256,

		PLUS = 45,

		N0 = 48,
		N1 = 49,
		N2 = 50,
		N3 = 51,
		N4 = 52,
		N5 = 53,
		N6 = 54,
		N7 = 55,
		N8 = 56,
		N9 = 57,

		RENAME_KEY_NEXT_TO_PLUS = 61,
		RENAME_KEY_NEXT_TO_N1 = 96,
		RENAME_KEY_NEXT_TO_L_SHIFT = 162,
		RENAME_KEY_NEXT_TO_Å = 93,

		BACKSPACE = 259,

		INSERT = 260,
		HOME = 268,
		PG_UP = 266,
		DELETE = 261,
		END = 269,
		PG_DOWN = 267,

		LEFT = 263,
		UP = 265,
		RIGHT = 262,
		DOWN = 264,

		TAB = 258,
		CAPS_LOCK = 280,
		
		L_SHIFT = 340,
		R_SHIFT = 344,

		L_CTRL = 341,
		R_CTRL = 345,

		L_WINDOWS = 343,
		R_WINDOWS = 347,

		L_ALT= 342,
		R_ALT= 346,

		ENTER = 257,

		SPACE = 32,

		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,


		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		Å = 91,
		Ä = 39,
		Ö = 59,

		COMMA = 44,
		DOT = 46,

		ABSTERIX = 92,

	};
}
