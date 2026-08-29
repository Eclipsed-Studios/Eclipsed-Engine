#include "MoveBridge.h"

#include "EclipsedEngine/Components/Transform2D.h"
#include "Core/Timer.h"

void MoveBridge::Interact()
{
	interacted = true;
}

void MoveBridge::Update()
{
	if (!interacted) return;

	auto pos = gameObject->transform->GetPosition();
	float x = std::lerp(pos.x, targetPos->x, Eclipse::Core::Timer::GetDeltaTime());
	float y = std::lerp(pos.y, targetPos->y, Eclipse::Core::Timer::GetDeltaTime());

	gameObject->transform->SetPosition({ x, y });
}