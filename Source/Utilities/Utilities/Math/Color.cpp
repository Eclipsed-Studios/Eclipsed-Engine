#include "Color.h"

rapidjson::Value ENGINE_NAMESPACE::Math::Color::Save(rapidjson::Document::AllocatorType& allocator) const
{
	return rapidjson::Value();
}

void ENGINE_NAMESPACE::Math::Color::Load(const rapidjson::Value& aValue)
{
}

float ENGINE_NAMESPACE::Math::Color::GetComponent(ColorComponent aComponent)
{
	if (aComponent == ColorComponent::Red)
	{
		return r;
	}
	else if (aComponent == ColorComponent::Green)
	{
		return g;
	}
	else if (aComponent == ColorComponent::Blue)
	{
		return b;
	}
	else if (aComponent == ColorComponent::Alpha)
	{
		return a;
	}

	return g;

}
