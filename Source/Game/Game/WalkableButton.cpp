#include "WalkableButton.h"

#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"

#include "ECS/ComponentManager.h"
#include <EclipsedEngine/DebugLogger.h>
#include "Core/Timer.h"

#include "EclipsedEngine/Components/Transform2D.h"

#include "Door.h"

#include "Core/EventSystem/EventSystem.h"

void WalkableButton::Update()
{
	if (!wasPressed) return;

	timer += Eclipse::Core::Timer::GetDeltaTime();
	if (timer >= buttonDownTime)
	{
		wasPressed = false;

		for (auto child : gameObject->GetChildren())
		{
			if (child->GetName() == "Button On")
			{
				Eclipse::SpriteRenderer2D* rend = child->GetComponent<Eclipse::SpriteRenderer2D>();
				rend->gameObject->transform->SetPosition({ 1000000.f, 0 });
			}

			if (child->GetName() == "Button Off")
			{
				Eclipse::SpriteRenderer2D* rend = child->GetComponent<Eclipse::SpriteRenderer2D>();
				rend->gameObject->transform->SetPosition({ 0, 0.002f });
			}
		}
	}
}

void WalkableButton::OnTriggerEnter(Eclipse::GameObject* Other)
{
	if (Other->GetName() != "Player")  return;

	for (auto child : gameObject->GetChildren())
	{
		if (child->GetName() == "Button On")
		{
			Eclipse::SpriteRenderer2D* rend = child->GetComponent<Eclipse::SpriteRenderer2D>();
			rend->gameObject->transform->SetPosition({ 0, 0 });
		}

		if (child->GetName() == "Button Off")
		{
			Eclipse::SpriteRenderer2D* rend = child->GetComponent<Eclipse::SpriteRenderer2D>();
			rend->gameObject->transform->SetPosition({ 1000000.f,  });
		}
	}

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
