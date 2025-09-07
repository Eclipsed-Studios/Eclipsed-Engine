#include "Game.h"

#include "Input/InputMapper.h"

#include "Components/Rendering/SpriteRenderer2D.h"
#include "Components/Rendering/SpriteSheetAnimator.h"
#include "Components/Rendering/Camera.h"
#include "Components/Transform2D.h"
#include "Components/Player.h"
#include "Components/Physics/RigidBody2D.h"
#include "Components/Physics/BoxCollider2D.h"
#include "Components/Physics/PolygonCollider2D.h"
#include "Components/AudioSource.h"

#include "Components/PlayerMovement.h"

#include "ECS/ComponentManager.h"
#include "MainSingleton.h"

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
			Material* matrial = new Material();
			matrial->SetTexture(ASSET_PATH "Sprites/Pink_Monster.png");

			int go = 1;
			SpriteRenderer2D* rend = ComponentManager::AddComponent<SpriteRenderer2D>(go);
			Transform2D* transform = ComponentManager::AddComponent<Transform2D>(go);
			transform->SetScale(8.f, 8.f);

			BoxCollider2D* boxCollider = ComponentManager::AddComponent<BoxCollider2D>(go);
			boxCollider->SetScale(Math::Vector2f(0.5f, 1.f));
			boxCollider->myLayer = Layer::Player;

			AudioSource* audio = ComponentManager::AddComponent<AudioSource>(go);
			audio->SetAudioClip(ASSET_PATH "Sounds/peak.mp3");

			RigidBody2D* rb = ComponentManager::AddComponent<RigidBody2D>(go);
			rb->SetRotationLocked(true);

			ComponentManager::AddComponent<Player>(go);
			ComponentManager::AddComponent<PlayerMovement>(go);

			rend->SetMaterial(matrial);

			SpriteSheetAnimator2D* animation = ComponentManager::AddComponent<SpriteSheetAnimator2D>(go);

			//ResourcePointer<SpriteSheetAnimation> anim = Resources::Get<SpriteSheetAnimation>(ASSET_PATH "Sprites/DefaultAnimation.json");


			animation->SetSpriteSheet(ASSET_PATH "Sprites/DefaultAnimation.json");
		}

		// Ground
		{
			Material* matrial = new Material();
			matrial->SetTexture(ASSET_PATH "Sprites/Environment/013.png");

			int go = 2;
			SpriteRenderer2D* rend = ComponentManager::AddComponent<SpriteRenderer2D>(go);
			Transform2D* transform = ComponentManager::AddComponent<Transform2D>(go);
			transform->SetPosition(0.4f, -0.6f);
			transform->SetScale(matrial->myTexture->GetTextureSizeEngineUnits() * 5.f);
			BoxCollider2D* boxCollider = ComponentManager::AddComponent<BoxCollider2D>(go);
			boxCollider->SetScale(Math::Vector2f(1.f, 0.9f));
			boxCollider->myLayer = Layer::Ground;

			rend->SetMaterial(matrial);
		}

		// Ground
		{
			Material* matrial = new Material();
			matrial->SetTexture(ASSET_PATH "Sprites/Environment/012.png");

			int go = 3;
			SpriteRenderer2D* rend = ComponentManager::AddComponent<SpriteRenderer2D>(go);
			Transform2D* transform = ComponentManager::AddComponent<Transform2D>(go);
			transform->SetPosition(0, -0.7f);
			transform->SetScale(matrial->myTexture->GetTextureSizeEngineUnits() * 5.f);
			PolygonCollider2D* polygonCollider = ComponentManager::AddComponent<PolygonCollider2D>(go);

			polygonCollider->AddPoint({ 0.f, 0.f });
			polygonCollider->AddPoint({ 0.f, 0.35f });
			polygonCollider->AddPoint({ 0.9f, 1.f });

			polygonCollider->AddPoint({ 1.f, 1.f });
			polygonCollider->AddPoint({ 1.f, 0.65f });
			polygonCollider->AddPoint({ 0.1f, 0.f });

			polygonCollider->myLayer = Layer::Ground;

			rend->SetMaterial(matrial);
		}

		// Ground
		{
			Material* matrial = new Material();
			matrial->SetTexture(ASSET_PATH "Sprites/Environment/013.png");

			int go = 4;
			SpriteRenderer2D* rend = ComponentManager::AddComponent<SpriteRenderer2D>(go);
			Transform2D* transform = ComponentManager::AddComponent<Transform2D>(go);
			transform->SetPosition(-0.4f, -0.8f);
			transform->SetScale(matrial->myTexture->GetTextureSizeEngineUnits() * 5.f);
			BoxCollider2D* boxCollider = ComponentManager::AddComponent<BoxCollider2D>(go);
			boxCollider->SetScale(Math::Vector2f(1.f, 0.9f));
			boxCollider->myLayer = Layer::Ground;

			rend->SetMaterial(matrial);
		}

		// Camera
		{
			int go = 5;
			Transform2D* transform = ComponentManager::AddComponent<Transform2D>(go);
			transform->SetPosition(0.f, 0.f);

			ComponentManager::AddComponent<Camera>(go);
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