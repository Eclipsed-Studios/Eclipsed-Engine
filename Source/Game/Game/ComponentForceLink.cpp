#include "ComponentForcelink.h"

#include "EclipsedEngine/Reflection/Registry/ComponentRegistry.h"
#include "EclipsedEngine/Components/ComponentForcelink.h"

#include "PlayerMovement.h"
#include "Player.h"
#include "SmoothCameraMover.h"
#include "SquishAnimator.h"
#include "ParallaxBackground.h"
#include "ParallaxBackgroundObject.h"

#include "Companion.h"
#include "Door.h"

#include "DeathBarrier.h"
#include "InteractableKey.h"
#include "InteractableButton.h"
#include "PlayerInteract.h"
#include "WalkableButton.h"

#include "ChangePlayerValuesOnTrigger.h"

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
	COMP_REG(Player);
	COMP_REG(SmoothCameraMover);
	COMP_REG(SquishAnimator);
	COMP_REG(ParallaxBackground);
	COMP_REG(WalkableButton);
	COMP_REG(ParallaxBackgroundObject);
	COMP_REG(Door);

	COMP_REG(DeathBarrier);
	COMP_REG(InteractableKey);
	COMP_REG(InteractableButton);
	COMP_REG(PlayerInteract);

	COMP_REG(ChangePlayerValuesOnTrigger);

}
