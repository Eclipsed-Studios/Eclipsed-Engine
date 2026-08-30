#pragma once

#include "CompanionInteraction.h"

#include "Assets/Assets/TextureAsset.h"

class ChangeSprite : public CompanionInteraction
{
	COMPONENT_BASE_2(ChangeSprite, 0);
public:
	void Interact() override;

private:
	SERIALIZED_FIELD(Eclipse::Assets::Texture, NewSprite);
};