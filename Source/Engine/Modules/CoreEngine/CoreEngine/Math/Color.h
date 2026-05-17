#pragma once

#include "Vector/Vector4.h"
#include "CoreEngine/Settings/SettingsBase.hpp"

namespace Eclipse::Math
{
	constexpr float twoFify = 1.f / 255.f;

	class Color final
	{
	public:
		Color() = default;
		
		Color(float R, float G, float B, float A);
		Color(int aHexValue);

		int32_t GetHexValue();

		Vector4f ToVector() { return Vector4f(r, g, b, a); }

		SERIALIZE(MAKE_NVP(r),
			MAKE_NVP(g),
			MAKE_NVP(b),
			MAKE_NVP(a))

	public:
		union
		{
			struct { float r, g, b, a; };
			float data[4] = { 1, 1, 1, 1 };
		};
	};
}