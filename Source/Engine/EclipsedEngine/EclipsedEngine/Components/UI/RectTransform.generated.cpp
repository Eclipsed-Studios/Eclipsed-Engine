#include "RectTransform.h"
#include "Reflection/ReflectionCommon.hpp"

#include "EclipsedEngine/EclipsedRuntime.h"

using namespace Eclipse;


BASE(RectTransform);

TYPE_INFO_STRUCT(RectTransform)
{
	TYPE(RectTransform);
	NAME(RectTransform);

	PROPERTY(Math::Vector2f, Position);
	PROPERTY(Math::Vector2f, WidthHeightPX);
	PROPERTY(bool, ScaleWithCanvasX);
	PROPERTY(bool, ScaleWithCanvasY);
	PROPERTY(bool, AlignLeft);
	PROPERTY(bool, AlignTop);
	PROPERTY(bool, AlignRight);
	PROPERTY(bool, AlignBottom);

	PROPERTY_LIST(
		&Position,
		&WidthHeightPX,
		&ScaleWithCanvasX,
		&ScaleWithCanvasY,
		&AlignLeft,
		&AlignTop,
		&AlignRight,
		&AlignBottom
	);

	PROPERTY_COUNT(8);
	GETTER_METHODS;
};

REGISTRATOR(RectTransform);
