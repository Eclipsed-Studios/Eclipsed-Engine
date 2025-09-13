#include "Component.h"

#include "ImGui/ImGui/imgui.h"

namespace Eclipse
{
	Component::Component(unsigned updatePriority) : myUpdateStartPriority(updatePriority)
	{
	}
}