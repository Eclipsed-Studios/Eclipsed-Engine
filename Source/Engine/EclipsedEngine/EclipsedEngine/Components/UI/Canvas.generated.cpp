#include "Canvas.h"
#include "Reflection/ReflectionCommon.hpp"

#include "EclipsedEngine/EclipsedRuntime.h"
using namespace Eclipse;

BASE(Canvas);

TYPE_INFO_STRUCT(Canvas)
{
	TYPE(Canvas);
	NAME(Canvas);

	PROPERTY(Math::Vector2f, ReferenceResolution);
	PROPERTY(bool, WorldSpace);

	PROPERTY_LIST(
		&ReferenceResolution,
		&WorldSpace
	);

	PROPERTY_COUNT(2);
	GETTER_METHODS;
};

REGISTRATOR(Canvas);
