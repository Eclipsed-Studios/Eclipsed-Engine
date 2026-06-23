#include "Button.h"
#include "Reflection/ReflectionCommon.hpp"

#include "EclipsedEngine/EclipsedRuntime.h"
using namespace Eclipse;

BASE(Button);

TYPE_INFO_STRUCT(Button)
{
	TYPE(Button);
	NAME(Button);

	PROPERTY_LIST(
		nullptr
	);

	PROPERTY_COUNT(0);
	GETTER_METHODS;
};

REGISTRATOR(Button);
