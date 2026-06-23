#include "Transform2D.h"
#include "Reflection/ReflectionCommon.hpp"

#include "EclipsedEngine/EclipsedRuntime.h"

using namespace Eclipse;


BASE(Transform2D);

TYPE_INFO_STRUCT(Transform2D)
{
	TYPE(Transform2D);
	NAME(Transform2D);

	PROPERTY(Math::Vector2f, position);
	PROPERTY(Math::Vector2f, scale);
	PROPERTY(float, rotation);

	PROPERTY_LIST(
		&position,
		&scale,
		&rotation
	);

	PROPERTY_COUNT(3);
	GETTER_METHODS;
};

REGISTRATOR(Transform2D);
