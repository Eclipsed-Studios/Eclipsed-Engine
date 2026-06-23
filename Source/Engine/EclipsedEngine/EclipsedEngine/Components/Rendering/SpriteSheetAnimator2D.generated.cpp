#include "SpriteSheetAnimator2D.h"
#include "Reflection/ReflectionCommon.hpp"

#include "EclipsedEngine/EclipsedRuntime.h"


using namespace Eclipse;


BASE(SpriteSheetAnimator2D);

TYPE_INFO_STRUCT(SpriteSheetAnimator2D)
{
	TYPE(SpriteSheetAnimator2D);
	NAME(SpriteSheetAnimator2D);

	PROPERTY(float, myTimePerFrame);
	PROPERTY(int, myCurrentFrame);
	PROPERTY(bool, myLoop);

	PROPERTY_LIST(
		&myTimePerFrame,
		&myCurrentFrame,
		&myLoop
	);

	PROPERTY_COUNT(3);
	GETTER_METHODS;
};

REGISTRATOR(SpriteSheetAnimator2D);
