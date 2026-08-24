#include "SquishAnimator.h"

#include "EclipsedEngine/Components/Transform2D.h"
#include "Core/Math/Vector/Vector2.h"

#include "Core/Timer.h"

#include "Physics/PhysicsEngine.h"

void SquishAnimator::Update()
{
	Eclipse::Ray ray;
	ray.direction = Eclipse::Math::Vector2f(0.f, -1.f);
	ray.position = gameObject->transform->GetPosition();

	Eclipse::HitResults Hitresults;

	Eclipse::PhysicsEngine::RayCast(ray, Hitresults, 0.1f);

	bool IsOnGround = false;

	for (Eclipse::HitResult& hitResult : Hitresults.results)
	{
		if (gameObject->GetID() == hitResult.gameobject)
			continue;

		IsOnGround = true;

		break;
	}

	//if (!WasOnGround && IsOnGround)
	//	StartSquish();

	WasOnGround = IsOnGround;

	if (IsSquishing)
	{
		if (CurrentSquish < 0)
		{
			IsSquishing = false;
			CurrentSquish = 0;
			SquishOut = 1;

			gameObject->transform->SetScale(OriginalScale);
		}
		else if (CurrentSquish >= SquishAmount)
		{
			SquishOut = -1;
		}


		float deltatime = Eclipse::Core::Timer::GetDeltaTime();
		CurrentSquish += SquishTime * deltatime * SquishOut;

		Eclipse::Math::Vector2f CurrentScale = gameObject->transform->GetScale();

		CurrentScale.y = OriginalScale.y + CurrentSquish;
		CurrentScale.x = OriginalScale.x - CurrentSquish * 2;

		gameObject->transform->SetScale(CurrentScale);
	}
}

void SquishAnimator::Start()
{
	OriginalScale = gameObject->transform->GetScale();
}

void SquishAnimator::StartSquish()
{
	IsSquishing = true;
}

void SquishAnimator::CollisionStart()
{
	float test = 90;
}