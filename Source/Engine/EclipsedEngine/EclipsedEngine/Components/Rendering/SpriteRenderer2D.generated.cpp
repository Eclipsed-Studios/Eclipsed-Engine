#include "SpriteRenderer2D.h"
#include "Reflection/ReflectionCommon.hpp"

#include "EclipsedEngine/EclipsedRuntime.h"

using namespace Eclipse;


BASE(SpriteRenderer2D);

TYPE_INFO_STRUCT(SpriteRenderer2D)
{
	TYPE(SpriteRenderer2D);
	NAME(SpriteRenderer2D);

	PROPERTY(Assets::Texture, sprite);
	PROPERTY(Assets::Material, material);

	PROPERTY_LIST(
		&sprite,
		&material
	);

	PROPERTY_COUNT(2);
	GETTER_METHODS;
};

REGISTRATOR(SpriteRenderer2D);
