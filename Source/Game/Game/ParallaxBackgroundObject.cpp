#include "ParallaxBackgroundObject.h"

#include "EclipsedEngine/ECS/ObjectManager.h"
#include "EclipsedEngine/Components/Transform2D.h"
#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"

#include "PlayerMovement.h"

#include "Core/Math/Random.h"
#include "Core/Timer.h"



void ParallaxBackgroundObject::Awake()
{
	rend = gameObject->GetComponent<Eclipse::SpriteRenderer2D>();
	startingPos = gameObject->transform->GetPosition();

	rend->ZIndex = myZIndex;

	if (DarkenByDepth)
	{
		float darkness = (MinZIndex - myZIndex) / (MaxZIndex - MinZIndex);
		darkness = std::clamp(darkness, 0.f, 1.f);

		float brightness = 1.f - darkness * 0.5f;

		auto color = rend->GetColor();
		color.r *= brightness;
		color.g *= brightness;
		color.b *= brightness;
		rend->SetColor(color);
	}
}

void ParallaxBackgroundObject::Update()
{
	if (Rotate)
	{
		currentRotation = gameObject->transform->GetRotation() + RotationSpeed * Eclipse::Core::Timer::GetDeltaTime();
		gameObject->transform->SetRotation(currentRotation);
	}

	float x = gameObject->transform->GetPosition().x;

	float parallax = 1.0f - (myZIndex - MinZIndex) / (MaxZIndex - MinZIndex);
	parallax = std::clamp(parallax, 0.f, 1.f);

	float newX = startingPos.x + PlayerMovement::Pos.x * parallax;
	float newY = startingPos.y + PlayerMovement::Pos.y * parallax * YScaling;

	gameObject->transform->SetPosition({ newX, newY });
}