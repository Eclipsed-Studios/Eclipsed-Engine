#pragma once

#include "EclipsedEngine/Components/Component.h"

namespace Eclipse { class TextRenderer; }

class TutorialComp : public Eclipse::Component
{
	COMPONENT_BASE_2(TutorialComp, 0);

public:
	void Start() override;
	void Update() override;

private:
	Eclipse::TextRenderer* textRenderer;
};