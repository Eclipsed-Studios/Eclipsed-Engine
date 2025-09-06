#include "Game.h"

#include "Input/InputMapper.h"

#include <Components/Rendering/SpriteRenderer2D.h>
#include <Components/Rendering/SpriteSheetAnimator.h>
#include <Components/Transform2D.h>
#include <Components/Player.h>
#include <Components/Physics/RigidBody2D.h>
#include <Components/Physics/BoxCollider2D.h>
#include <Components/AudioSource.h>

#include "Components/PlayerMovement.h"

#include <ECS/ComponentManager.h>
#include <MainSingleton.h>

#include "Timer.h"
#include "Input/Input.h"
#include "Input/Keycodes.h"

#include "PhysicsEngine.h"

#include "AssetManagement/Resources/SpriteSheetAnimation.h"

namespace ENGINE_NAMESPACE
{
	void Game::Init()
	{
		// Player
		{
			int go = 1;
			SpriteRenderer2D* rend = ComponentManager::AddComponent<SpriteRenderer2D>(go);
			Transform2D* transform = ComponentManager::AddComponent<Transform2D>(go);
			transform->SetScale(60.f, 60.f);

			BoxCollider2D* boxCollider = ComponentManager::AddComponent<BoxCollider2D>(go);
			boxCollider->SetScale(Math::Vector2f(1.f, 1.f));
			boxCollider->myLayer = Layer::Player;

			AudioSource* audio = ComponentManager::AddComponent<AudioSource>(go);
			audio->SetAudioClip(ASSET_PATH "Sounds/T.mp3");

			RigidBody2D* rb = ComponentManager::AddComponent<RigidBody2D>(go);
			rb->SetRotationLocked(true);

			Material* matrial = new Material();
			matrial->SetTexture(ASSET_PATH "Sprites/Pink_Monster.png");

			ComponentManager::AddComponent<Player>(go);
			ComponentManager::AddComponent<PlayerMovement>(go);

			rend->SetMaterial(matrial);

			SpriteSheetAnimator2D* animation = ComponentManager::AddComponent<SpriteSheetAnimator2D>(go);

			//ResourcePointer<SpriteSheetAnimation> anim = Resources::Get<SpriteSheetAnimation>(ASSET_PATH "Sprites/DefaultAnimation.json");


			animation->SetSpriteSheet(ASSET_PATH "Sprites/DefaultAnimation.json");
		}

		// Ground
		{
			int go = 2;
			SpriteRenderer2D* rend = ComponentManager::AddComponent<SpriteRenderer2D>(go);
			Transform2D* transform = ComponentManager::AddComponent<Transform2D>(go);
			transform->SetPosition(0.4f, -0.6f);
			transform->SetScale(130, 50.f);
			BoxCollider2D* boxCollider = ComponentManager::AddComponent<BoxCollider2D>(go);
			boxCollider->SetScale(Math::Vector2f(1.f, 0.9f));
			boxCollider->myLayer = Layer::Ground;

			Material* matrial = new Material();
			matrial->SetTexture(ASSET_PATH "Sprites/Environment/013.png");

			rend->SetMaterial(matrial);
		}

		// Ground
		{
			int go = 3;
			SpriteRenderer2D* rend = ComponentManager::AddComponent<SpriteRenderer2D>(go);
			Transform2D* transform = ComponentManager::AddComponent<Transform2D>(go);
			transform->SetPosition(0, -0.7f);
			transform->SetScale(130, 50.f);
			BoxCollider2D* boxCollider = ComponentManager::AddComponent<BoxCollider2D>(go);
			boxCollider->SetScale(Math::Vector2f(1.f, 0.9f));
			boxCollider->myLayer = Layer::Ground;

			Material* matrial = new Material();
			matrial->SetTexture(ASSET_PATH "Sprites/Environment/012.png");

			rend->SetMaterial(matrial);
		}
	}

	void Game::Update()
	{
		int go = 1;
		AudioSource* au = GetComp(AudioSource, go);
		if (Input::GetKeyDown(Keycode::I)) au->Play();
		else if (Input::GetKeyDown(Keycode::O)) au->Pause();
		else if (Input::GetKeyDown(Keycode::P)) au->Stop();
	}
}