#pragma once

#include "Interactable.h"
#include "Assets/Assets/TextureAsset.h"

class WalkableButton : public Eclipse::Component
{
	COMPONENT_BASE_2(WalkableButton, 0);

public:
	void Update() override;
	void OnTriggerEnter(Eclipse::GameObject* Other) override;
	void OnTriggerExit(Eclipse::GameObject* Other) override;

private:
	float timer = 0.f;
	bool wasPressed = false;

	SERIALIZED_FIELD_DEFAULT(std::string, doorName, "");

	
	SERIALIZED_FIELD_DEFAULT(float, buttonDownTime, 0.f);


	SERIALIZED_FIELD(Eclipse::Assets::Texture, buttonPressedTexture);
	SERIALIZED_FIELD(Eclipse::Assets::Texture, buttonUpTexture);
};