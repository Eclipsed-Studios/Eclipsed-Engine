#include "Color.h"


namespace ENGINE_NAMESPACE
{
	Math::Color::Color(float R, float G, float B, float A)
		: r(R), g(G), b(B), a(A)
	{

	}

	Math::Color::Color(int aHexValue)
	{
		r = ((aHexValue >> 16) & 0xFF) / 255.f;
		g = ((aHexValue >> 8) & 0xFF) / 255.f;
		b = ((aHexValue) & 0xFF) / 255.f;
	}

		rapidjson::Value Math::Color::Save(rapidjson::Document::AllocatorType& allocator) const
	{
		rapidjson::Value obj(rapidjson::kObjectType);

		obj.AddMember("r", r, allocator);
		obj.AddMember("g", g, allocator);
		obj.AddMember("b", b, allocator);
		obj.AddMember("a", a, allocator);

		return obj;
	}

	void Math::Color::Load(const rapidjson::Value& aValue)
	{
		if (aValue.HasMember("r") && aValue["r"].IsNumber())
		{
			r = aValue["r"].GetFloat();
		}

		if (aValue.HasMember("g") && aValue["g"].IsNumber())
		{
			g = aValue["g"].GetFloat();
		}

		if (aValue.HasMember("b") && aValue["b"].IsNumber())
		{
			b = aValue["b"].GetFloat();
		}

		if (aValue.HasMember("a") && aValue["a"].IsNumber())
		{
			a = aValue["a"].GetFloat();
		}
	}
}