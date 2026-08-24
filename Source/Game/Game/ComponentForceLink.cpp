#include "ComponentForcelink.h"

#include "EclipsedEngine/Reflection/Registry/ComponentRegistry.h"
#include "EclipsedEngine/Components/ComponentForcelink.h"

#include "PlayerMovement.h"
#include "SmoothCameraMover.h"
#include "SquishAnimator.h"
#include "ParallaxBackground.h"
#include "ParallaxBackgroundObject.h"

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

	COMP_REG(PlayerMovement);
	COMP_REG(SmoothCameraMover);
	COMP_REG(SquishAnimator);
	COMP_REG(ParallaxBackground);
	COMP_REG(ParallaxBackgroundObject);

}
