#include "Rect.h"

namespace Eclipse::Math
{
	rapidjson::Value Math::Rect::Save(rapidjson::Document::AllocatorType& allocator) const
	{
		rapidjson::Value minRect(rapidjson::kObjectType);

		minRect.AddMember("x", min.x, allocator);
		minRect.AddMember("y", min.y, allocator);


		rapidjson::Value maxRect(rapidjson::kObjectType);

		maxRect.AddMember("x", max.x, allocator);
		maxRect.AddMember("y", max.y, allocator);


		rapidjson::Value val(rapidjson::kObjectType);

		val.AddMember("min", minRect.Move(), allocator);
		val.AddMember("max", maxRect.Move(), allocator);

		return val;
	}
	void Rect::Load(const rapidjson::Value& aValue)
	{
		const rapidjson::Value& minVal = aValue["min"];
		const rapidjson::Value& maxVal = aValue["max"];
		

		if (minVal.HasMember("x") && minVal["x"].IsNumber())
			min.x = static_cast<float>(minVal["x"].GetDouble());

		if (minVal.HasMember("y") && minVal["y"].IsNumber())
			min.y = static_cast<float>(minVal["y"].GetDouble());

		if (maxVal.HasMember("x") && maxVal["x"].IsNumber())
			max.x = static_cast<float>(maxVal["x"].GetDouble());

		if (maxVal.HasMember("y") && maxVal["y"].IsNumber())
			max.y = static_cast<float>(maxVal["y"].GetDouble());
	}
}