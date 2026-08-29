#include "PlayerHatController.h"

#include "Input/Input.h"
#include "HatManager.h"

#include"EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"
#include"EclipsedEngine/Components/Audio/AudioEmitter.h"

void PlayerHatController::Start()
{
	HatManager::Reset();

	for (auto child : gameObject->GetChildren())
	{
		const std::string name = child->GetName();
		if (name == "Hat")
		{
			hatRend = child->GetComponent<Eclipse::SpriteRenderer2D>();

			if (!HatManager::HasHats())
			{
				HatManager::AddHat(Eclipse::Math::Color(0.f, 0.f, 0.f, 0.f));
			}
		}
		else if (name == "Hat-Change Sound")
		{
			sound = child->GetComponent<Eclipse::AudioEmitter>();
		}
	}

}

void PlayerHatController::Update()
{
	if (HatManager::HasHats() && Eclipse::Input::GetKeyDown(Eclipse::Keycode::H))
	{
		HatManager::CycleNextHat();
		sound->Play();
	}

	if (HatManager::HasHats())
	{
		hatRend->SetColor(HatManager::GetCurrentHat());
	}
}