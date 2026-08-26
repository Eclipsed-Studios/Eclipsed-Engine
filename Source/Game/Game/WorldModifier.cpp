#include "WorldModifier.h"

#include "ECS/ComponentManager.h"

void WorldModifier::ToggleObject()
{
	Eclipse::ComponentManager::FindObjectByName(NameOfObjectToToggle->c_str());
}