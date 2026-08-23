#include "ComponentForcelink.h"

#include "EclipsedEngine/Reflection/Registry/ComponentRegistry.h"
#include "EclipsedEngine/Components/ComponentForcelink.h"
#include "EclipsedEngine/Components/Audio/AudioListener.h"

#include "PlayerMovement.h"
#include "SmoothCameraMover.h"

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

}
