#pragma once

#include <initializer_list>

#include "Interfaces/Serializable.h"

namespace Eclipse::Math
{
	class Color final : public ISerializable
	{
	public:
		Color(float R = 1.f, float G = 1.f, float B  =1.f, float A  = 1.f);
		Color(int aHexValue);

	public:
		rapidjson::Value Save(rapidjson::Document::AllocatorType& allocator) const override;
		void Load(const rapidjson::Value& aValue) override;

	public:
		union
		{
			struct { float r, g, b, a; };
			float data[4] = { 1,1,1,1 };
		};
	};
}