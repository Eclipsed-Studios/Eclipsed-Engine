#include "Companion.h"

#include "Input/Input.h"
#include "Core/Timer.h"
#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"
#include "EclipsedEngine/Components/Transform2D.h"

#include "PlayerMovement.h"

void Companion::Update()
{
	float dt = Eclipse::Core::Timer::GetDeltaTime();
	time += dt;

	float px = PlayerMovement::Pos.x;
	float py = PlayerMovement::Pos.y;

	float xOffset =
		std::sin(time * horizontalSpeed) * horizontalAmplitude +
		std::sin(time * horizontalSecondarySpeed) * horizontalSecondaryAmplitude;

	float yOffset =
		std::sin(time * verticalSpeed) * verticalAmplitude +
		std::sin(time * verticalSecondarySpeed) * verticalSecondaryAmplitude;

	float xTarget = px + xOffset;
	float yTarget = py + headOffset + yOffset;

	float cx = gameObject->transform->GetPosition().x;
	float cy = gameObject->transform->GetPosition().y;

	float x = std::lerp(cx, xTarget, dt);
	float y = std::lerp(cy, yTarget, dt);

	gameObject->transform->SetPosition({ x, y });
}