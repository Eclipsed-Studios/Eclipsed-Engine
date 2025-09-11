#pragma once

#include "rapidjson/rapidjson/document.h"

namespace Eclipse
{
	class ISerializable
	{
	public:
		virtual rapidjson::Value Save(rapidjson::Document::AllocatorType& allocator) const = 0;
		virtual void Load(const rapidjson::Value& aValue) = 0;
	};
}