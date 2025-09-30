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


#include "Scenes/SceneManager.h"
#include "ECS/ECS.hpp"

namespace Eclipse
{
	void Game::Init()
	{
#ifdef _GAME
		SceneManager::LoadScene(0);
#endif 
	}
	}