#include "ParallaxBackground.h"

#include "EclipsedEngine/ECS/ObjectManager.h"
#include "EclipsedEngine/Components/Transform2D.h"
#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"

#include "PlayerMovement.h"

#include "Core/Math/Random.h"
#include "Core/Timer.h"

void ParallaxBackgroundObject::Start()
{
	startingPosX = Random::RandRange<float>(-2.f, 1.f);
	posY = Random::RandRange<float>(-1.f, 1.f);
	gameObject->transform->SetPosition({ startingPosX, posY });

	rot = Random::RandRange<float>(0.f, 360.f);
	gameObject->transform->SetRotation(rot);

	float scale = Random::RandRange<float>(2.f, 7.f);
	gameObject->transform->SetScale(Eclipse::Math::Vector2f(scale, scale));

	rend = gameObject->GetComponent<Eclipse::SpriteRenderer2D>();
	float zIndex = Random::RandRange<float>(-100.f , -95.f);
	rend->ZIndex = zIndex;

	float darkness = (-95.f - zIndex) / 5.f;
	darkness = std::clamp(darkness, 0.f, 1.f);

	float brightness = 1.f - darkness * 0.5f;

	auto color = rend->GetColor();
	color.r *= brightness;
	color.g *= brightness;
	color.b *= brightness;
	rend->SetColor(color);
}

void ParallaxBackgroundObject::Update()
{
	rot += Eclipse::Core::Timer::GetDeltaTime();
	gameObject->transform->SetRotation(rot);

	float x = gameObject->transform->GetPosition().x;

	float parallax = (rend->GetZIndex() + 100.f) / 90.f;
	parallax = std::clamp(parallax, 0.f, 1.f);

	float cameraX = PlayerMovement::PosX;

	float newX = startingPosX + cameraX * parallax;

	gameObject->transform->SetPosition({ newX, posY });
}

void ParallaxBackground::Start()
{
	for (int i = 0; i < 100; i++)
	{
		auto obj = Eclipse::Instantiate(testSpawn, gameObject);
	}

}