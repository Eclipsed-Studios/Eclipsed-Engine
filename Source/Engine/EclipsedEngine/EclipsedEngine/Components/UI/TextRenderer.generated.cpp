#include "TextRenderer.h"
#include "Reflection/ReflectionCommon.hpp"

#include "EclipsedEngine/EclipsedRuntime.h"

using namespace Eclipse;

BASE(TextRenderer);

TYPE_INFO_STRUCT(TextRenderer)
{
	TYPE(TextRenderer);
	NAME(TextRenderer);

	inline static const TypedProperty<TYPE, String> myText{ "myText", sizeof(String), &TYPE::myText };;
	inline static const TypedProperty<TYPE, Math::Color> myTextColor{ "myTextColor", sizeof(Math::Color), &TYPE::myTextColor };;
	inline static const TypedProperty<TYPE, Assets::Font> font{ "font", sizeof(Assets::Font), &TYPE::font };;
	inline static const TypedProperty<TYPE, float> myFontSize{ "myFontSize", sizeof(float), &TYPE::myFontSize };;
	inline static const TypedProperty<TYPE, Math::Vector2f> myRect{ "myRect", sizeof(Math::Vector2f), &TYPE::myRect };;
	inline static const TypedProperty<TYPE, float> myCharacterSpacing{ "myCharacterSpacing", sizeof(float), &TYPE::myCharacterSpacing };;
	inline static const TypedProperty<TYPE, float> myEnterSpacing{ "myEnterSpacing", sizeof(float), &TYPE::myEnterSpacing };;
	inline static const TypedProperty<TYPE, float> mySpaceSpacing{ "mySpaceSpacing", sizeof(float), &TYPE::mySpaceSpacing };;

	PROPERTY_LIST(
		&myText,
		&myTextColor,
		&font,
		&myFontSize,
		&myRect,
		&myCharacterSpacing,
		&myEnterSpacing,
		&mySpaceSpacing
	);

	PROPERTY_COUNT(8);
	GETTER_METHODS;
};

REGISTRATOR(TextRenderer);
