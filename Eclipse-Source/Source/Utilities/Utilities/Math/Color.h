#pragma once

#include "Utilities/Interfaces/Serializable.h"

#include <initializer_list>
#include "Utilities/Math/Vector/Vector4.h"

namespace Eclipse::Math
{
	class Color final : public ISerializable
	{
	public:
		Color(float R = 1.f, float G = 1.f, float B = 1.f, float A = 1.f);
		Color(int aHexValue);

		int32_t GetHexValue() 
		{
			int R = static_cast<int>(r * 255.f);
			int G = static_cast<int>(g * 255.f);
			int B = static_cast<int>(b * 255.f);
			int A = static_cast<int>(a * 255.f);

			return (R << 24) | (G << 16) | (B << 8) | A;
		}

		Vector4f ToVector() { return { r, g, b, a }; }

	public:
		rapidjson::Value Save(rapidjson::Document::AllocatorType& allocator) const override;
		void Load(const rapidjson::Value& aValue) override;

	public:
		union
		{
			struct { float r, g, b, a; };
			float data[4] = { 1, 1, 1, 1 };
		};
	};
}