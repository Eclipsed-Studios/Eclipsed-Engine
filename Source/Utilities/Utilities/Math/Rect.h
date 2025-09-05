#pragma once

#include "Vector/Vector2.h"

#include "Interfaces/Serializable.h"

namespace ENGINE_NAMESPACE::Math
{
	class Rect : public ISerializable
	{
	public:
		rapidjson::Value Save(rapidjson::Document::AllocatorType& allocator) const override;
		void Load(const rapidjson::Value& aValue) override;

	public:
		Vector2f min = { 0,0 }, max = { 0,0 };
	};
}