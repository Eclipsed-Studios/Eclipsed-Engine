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
#include "Components/Physics/CircleCollider2D.h"
#include "Components/Physics/CapsuleCollider2D.h"
#include "Components/AudioSource.h"
#include "Components/UI/Button.h"

#include "Components/PlayerMovement.h"
#include "Components/PlayerCamera.h"

#include "ECS/ComponentManager.h"
#include "MainSingleton.h"

#include "Timer.h"
#include "Input/Input.h"
#include "Input/Keycodes.h"

#include "PhysicsEngine.h"

#include "AssetManagement/Resources/SpriteSheetAnimation.h"


#include "Scenes/SceneLoader.h"
#include "ECS/ECS.hpp"

//#define GAME
#define OBJECTS

namespace Eclipse
{
#ifdef GAME
	void Game::Init()
	{
		GameObject* playerObj = CreateGameObject();

#ifdef OBJECTS
		// Players
		{
			SpriteRenderer2D* rend = playerObj->AddComponent<SpriteRenderer2D>();
			Transform2D* transform = playerObj->GetComponent<Transform2D>();
			transform->SetScale(10.f, 10.f);

			CircleCollider2D* capsuleCollider = playerObj->AddComponent<CircleCollider2D>();
			capsuleCollider->myLayer = Layer::Player;

			capsuleCollider->SetRadius(1.f);
			//capsuleCollider->SetHalfHeight(1.f);

			RigidBody2D* rb = playerObj->AddComponent<RigidBody2D>();
			rb->SetRotationLocked(true);

			playerObj->AddComponent<Player>();
			playerObj->AddComponent<PlayerMovement>();

			rend->SetTexture(ASSET_PATH "Sprites/ScissorSprite/Scissors.png");

			SpriteSheetAnimator2D* animation = playerObj->AddComponent<SpriteSheetAnimator2D>();
			ResourcePointer<SpriteSheetAnimation> anim = Resources::Get<SpriteSheetAnimation>(ASSET_PATH "Sprites/ScissorSprite/ScissorAnimation.json");
			animation->SetSpriteSheet(ASSET_PATH "Sprites/ScissorSprite/ScissorAnimation.json");
		}

		// Ground
		{
			GameObject* obj = CreateGameObject();
			SpriteRenderer2D* rend = ComponentManager::AddComponent<SpriteRenderer2D>(obj->GetID());
			Transform2D* transform = ComponentManager::GetComponent<Transform2D>(obj->GetID());
			transform->SetPosition(0.46f, -0.625f);
			transform->SetScale(Math::Vector2f(25.f, 25.f));
			//transform->SetScale(matrial->myTexture->GetTextureSizeEngineUnits() * 6.f);
			BoxCollider2D* boxCollider = ComponentManager::AddComponent<BoxCollider2D>(obj->GetID());
			boxCollider->SetScale(Math::Vector2f(1.f, 0.9f));
			boxCollider->myLayer = Layer::Ground;

			rend->SetTexture(ASSET_PATH "Sprites/Environment/013.png");
		}

		// Ground
		{
			GameObject* obj = CreateGameObject();
			SpriteRenderer2D* rend = ComponentManager::AddComponent<SpriteRenderer2D>(obj->GetID());
			Transform2D* transform = ComponentManager::GetComponent<Transform2D>(obj->GetID());
			transform->SetPosition(0, -0.7f);


			PolygonCollider2D* polygonCollider = ComponentManager::AddComponent<PolygonCollider2D>(obj->GetID());

			polygonCollider->AddPoint({ 0.f, 0.f });
			polygonCollider->AddPoint({ 0.f, 0.4f });
			polygonCollider->AddPoint({ 0.9f, 1.f });

			polygonCollider->AddPoint({ 1.f, 1.f });
			polygonCollider->AddPoint({ 1.f, 0.6f });
			polygonCollider->AddPoint({ 0.2f, 0.f });

			polygonCollider->myLayer = Layer::Ground;


			transform->SetScale(Math::Vector2f(30.f, 30.f));

			rend->SetTexture(ASSET_PATH "Sprites/Environment/012.png");
		}

		// Ground
		{
			GameObject* obj = CreateGameObject();

			SpriteRenderer2D* rend = ComponentManager::AddComponent<SpriteRenderer2D>(obj->GetID());
			Transform2D* transform = ComponentManager::GetComponent<Transform2D>(obj->GetID());
			transform->SetPosition(-0.46f, -0.78f);
			transform->SetScale(Math::Vector2f(25.f, 25.f));
			BoxCollider2D* boxCollider = ComponentManager::AddComponent<BoxCollider2D>(obj->GetID());
			boxCollider->SetScale(Math::Vector2f(1.f, 0.9f));
			boxCollider->myLayer = Layer::Ground;

			rend->SetTexture(ASSET_PATH "Sprites/Environment/013.png");
		}
#endif

		// Camera
		{
			int go = 5;
			GameObject* obj = CreateGameObject();
			Transform2D* transform = ComponentManager::GetComponent<Transform2D>(obj->GetID());

			ComponentManager::AddComponent<Camera>(go);

			PlayerCamera* playerCamera = ComponentManager::AddComponent<PlayerCamera>(obj->GetID());
			playerCamera->myPlayerGO = playerObj->GetID();
		}

		ComponentManager::AwakeStartComponents();
	}

	void Game::Update()
	{
		int go = 1;
		AudioSource* au = GetComp(AudioSource, go);
		if (Input::GetKeyDown(Keycode::I)) au->Play();
		else if (Input::GetKeyDown(Keycode::O)) au->Pause();
		else if (Input::GetKeyDown(Keycode::P)) au->Stop();
	}
#else
	void Game::Init() {}
	void Game::Update() {}
#endif
	}