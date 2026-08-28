#include "WalkableButton.h"

#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"

#include "ECS/ComponentManager.h"
#include <EclipsedEngine/DebugLogger.h>
#include "Core/Timer.h"

#include "Door.h"

#include "Core/EventSystem/EventSystem.h"

void WalkableButton::Update()
{
	if (!wasPressed) return;

	timer += Eclipse::Core::Timer::GetDeltaTime();
	if (timer >= buttonDownTime)
	{
		wasPressed = false;

		Eclipse::SpriteRenderer2D* rend = gameObject->GetChild(0)->GetComponent<Eclipse::SpriteRenderer2D>();
		rend->SetSprite(buttonUpTexture);
	}
}

void WalkableButton::OnTriggerEnter(Eclipse::GameObject* Other)
{
	if (Other->GetName() != "Player")  return;

	Eclipse::SpriteRenderer2D* rend = gameObject->GetChild(0)->GetComponent<Eclipse::SpriteRenderer2D>();
	rend->SetSprite(buttonPressedTexture);

	Eclipse::GameObject* door = Eclipse::ComponentManager::FindObjectByName(doorName->c_str());
	if (door == nullptr) return;

	Door* doorComp = door->GetComponent<Door>();
	if (doorComp == nullptr) return;

	if (!doorComp->IsOpen())
	{
		doorComp->Open();
	}
}

void WalkableButton::OnTriggerExit(Eclipse::GameObject* Other)
{
	wasPressed = true;
	timer = 0.f;
}
