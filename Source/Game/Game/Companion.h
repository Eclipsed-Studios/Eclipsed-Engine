#pragma once

#include "EclipsedEngine/Components/Component.h"

namespace Eclipse
{
	class SpriteRenderer2D;
}

class Companion : public Eclipse::Component
{
	COMPONENT_BASE_2(Companion, 0);

public:
	void Update() override;

private:

private:
	SERIALIZED_FIELD_DEFAULT(float, headOffset, 1.0f);

	float time = 0.0f;

	SERIALIZED_FIELD_DEFAULT(float, horizontalAmplitude, 0.08f);
	SERIALIZED_FIELD_DEFAULT(float, horizontalSecondaryAmplitude, 0.03f);
	SERIALIZED_FIELD_DEFAULT(float, horizontalSpeed, 1.3f);
	SERIALIZED_FIELD_DEFAULT(float, horizontalSecondarySpeed, 2.7f);

	SERIALIZED_FIELD_DEFAULT(float, verticalAmplitude, 0.05f);
	SERIALIZED_FIELD_DEFAULT(float, verticalSecondaryAmplitude, 0.02f);
	SERIALIZED_FIELD_DEFAULT(float, verticalSpeed, 1.7f);
	SERIALIZED_FIELD_DEFAULT(float, verticalSecondarySpeed, 3.1f);
};