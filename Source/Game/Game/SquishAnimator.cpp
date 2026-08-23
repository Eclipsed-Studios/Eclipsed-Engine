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

	for (Eclipse::HitResult& hitResult : Hitresults.results)
	{
		if (gameObject->GetID() == hitResult.gameobject)
			continue;

		IsSquishing = true;
	}

	if (IsSquishing)
	{
		float deltatime = Eclipse::Core::Timer::GetDeltaTime();

		Eclipse::Math::Vector2f CurrentScale = gameObject->transform->GetScale();

		CurrentScale.y -= SquishTime * deltatime;
		CurrentScale.x += SquishTime * deltatime * 2;

		gameObject->transform->SetScale(CurrentScale);
	}
}

void SquishAnimator::Start()
{

}

void SquishAnimator::StartSquish()
{
	IsSquishing = true;
}

void SquishAnimator::CollisionStart()
{
	float test = 90;
}