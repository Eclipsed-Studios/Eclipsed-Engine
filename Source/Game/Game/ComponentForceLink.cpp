#include "ComponentForcelink.h"

#include "EclipsedEngine/Reflection/Registry/ComponentRegistry.h"
#include "EclipsedEngine/Components/ComponentForcelink.h"

#include "PlayerMovement.h"
#include "HatInteractable.h"
#include "SmoothCameraMover.h"
#include "SquishAnimator.h"
#include "ParallaxBackground.h"
#include "ParallaxBackgroundObject.h"

#include "Companion.h"
#include "Door.h"

#include "WorldModifier.h"
#include "InteractableKey.h"
#include "InteractableButton.h"
#include "PlayerInteract.h"
#include "PlayerHatController.h"
#include "WalkableButton.h"

//#ifndef ECL_EDITOR
//#include "Forcelink.h"
//#endif

template<typename T>
std::string GetName() {
	return typeid(T).name();
}

void ComponentForcelink::LinkComponents()
{
	Eclipse::EngineComponentForcelink::LinkComponents();

	COMP_REG(Companion);
	COMP_REG(PlayerMovement);
	COMP_REG(SmoothCameraMover);
	COMP_REG(SquishAnimator);
	COMP_REG(ParallaxBackground);
	COMP_REG(HatInteractable);
	COMP_REG(WalkableButton);
	COMP_REG(ParallaxBackgroundObject);
	COMP_REG(Door);
	COMP_REG(PlayerHatController);

	COMP_REG(WorldModifier);
	COMP_REG(InteractableKey);
	COMP_REG(InteractableButton);
	COMP_REG(PlayerInteract);

}
