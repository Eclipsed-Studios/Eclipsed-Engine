#include "Rect.h"

namespace ENGINE_NAMESPACE::Math
{
	rapidjson::Value Math::Rect::Save(rapidjson::Document::AllocatorType& allocator) const
	{
		rapidjson::Value val(rapidjson::kObjectType);

		val.AddMember("min", min.Save(allocator).Move(), allocator);
		val.AddMember("max", max.Save(allocator).Move(), allocator);

		return val;
	}
	void Rect::Load(const rapidjson::Value& aValue)
	{
		const rapidjson::Value& minVal = aValue["min"];
		const rapidjson::Value& maxVal = aValue["max"];
		
		min.Load(minVal);
		max.Load(maxVal);
	}
}