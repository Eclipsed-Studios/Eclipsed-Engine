#include "HatInteractable.h"

#include "Core/Timer.h"

#include "EclipsedEngine/Components/Transform2D.h"
#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"
#include "EclipsedEngine/Components/Audio/AudioEmitter.h"

#include "HatManager.h"

void HatInteractable::Interact()
{
	Eclipse::SpriteRenderer2D* rend = gameObject->GetComponent<Eclipse::SpriteRenderer2D>();
	if (rend)
	{
		HatManager::AddHat(rend->GetColor());
	}

	Eclipse::AudioEmitter* sound = Eclipse::ComponentManager::FindObjectByName("Hat Pickup Sound")->GetComponent<Eclipse::AudioEmitter>();
	if (sound)
	{
		sound->Play();
	}

	Eclipse::ComponentManager::Destroy(gameObject->GetID());
}

void HatInteractable::Update()
{
	timer += Eclipse::Core::Timer::GetDeltaTime();
	float y = std::cos(timer * floatForce) * floatSpeed;

	gameObject->transform->SetPosition({ gameObject->transform->GetPosition().x, y });
}
