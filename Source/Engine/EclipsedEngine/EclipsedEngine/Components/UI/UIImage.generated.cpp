#include "UIImage.h"
#include "Reflection/ReflectionCommon.hpp"

#include "EclipsedEngine/EclipsedRuntime.h"

using namespace Eclipse;


BASE(UIImage);

TYPE_INFO_STRUCT(UIImage)
{
	TYPE(UIImage);
	NAME(UIImage);

	PROPERTY(Assets::Texture, sprite);
	PROPERTY(Assets::Material, material);

	PROPERTY_LIST(
		&sprite,
		&material
	);

	PROPERTY_COUNT(2);
	GETTER_METHODS;

};

REGISTRATOR(UIImage);
