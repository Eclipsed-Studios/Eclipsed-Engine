#pragma once

#include "EclipsedEngine/Components/Component.h"

namespace Eclipse { class SpriteRenderer2D; class AudioEmitter; }

class PlayerHatController : public Eclipse::Component
{
	COMPONENT_BASE_2(PlayerHatController, 0);

public:
	void Start() override;
	void Update() override;


private:
	Eclipse::SpriteRenderer2D* hatRend;
	Eclipse::AudioEmitter* sound;
};