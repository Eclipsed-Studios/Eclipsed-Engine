#include "Component.h"

#include "ImGui/ImGui/imgui.h"

namespace ENGINE_NAMESPACE
{
	rapidjson::Value Component::Save(rapidjson::Document::AllocatorType& allocator) const
	{
		rapidjson::Value obj(rapidjson::kObjectType);

		obj.AddMember("owner", myComponentID, allocator);

		return obj;
	}

	void Component::Load(const rapidjson::Value& aValue)
	{
	}

	Component::Component(unsigned updatePriority) : myUpdateStartPriority(updatePriority)
	{
	}
}