#pragma once

#include <initializer_list>

#include "Interfaces/Serializable.h"

namespace ENGINE_NAMESPACE::Math
{
	enum class ColorComponent
	{
		Red, Green, Blue, Alpha
	};

	class Color final : public ISerializable
	{
	public:
		rapidjson::Value Save(rapidjson::Document::AllocatorType& allocator) const override;
		void Load(const rapidjson::Value& aValue) override;

	public:
		float GetComponent(ColorComponent aComponent);

	private:
		float r = 1, g = 1, b = 1, a = 1;
	};
}