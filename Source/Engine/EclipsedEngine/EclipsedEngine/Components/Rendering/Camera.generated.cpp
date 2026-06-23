#include "Camera.h"
#include "Reflection/ReflectionCommon.hpp"

#include "EclipsedEngine/EclipsedRuntime.h"

using namespace Eclipse;


BASE(Camera);

TYPE_INFO_STRUCT(Camera)
{
	TYPE(Camera);
	NAME(Camera);

	PROPERTY(float, CameraZoom);

	PROPERTY_LIST(
		&CameraZoom
	);

	PROPERTY_COUNT(1);
	GETTER_METHODS;
};

REGISTRATOR(Camera);
