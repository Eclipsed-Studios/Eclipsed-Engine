#include "Door.h"

#include "Input/Input.h"
#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"
#include "EclipsedEngine/Components/Transform2D.h"

void Door::Start()
{
	for (auto child : gameObject->GetChildren())
	{
		const std::string name = child->GetName();
		if (name == "Light")
		{
			lightRenderer = child->GetComponent<Eclipse::SpriteRenderer2D>();
		}
		else if (name == "Mover")
		{
			moverTransform = child->transform;
		}
		else if (name == "Collider")
		{
			colliderTransform = child->transform;
		}
	}

	//gameObject->GetChild()
	//lightRenderer = 
}

void Door::Update()
{
	if (Eclipse::Input::GetKeyDown(Eclipse::Keycode::J))
	{
		lightRenderer->SetColor(lightOnColor);

		Eclipse::Math::Vector2f pos = moverTransform->GetPosition();
		moverTransform->SetPosition({ pos.x, maxMoverY });

		colliderTransform->SetPosition({ 100000, 10000 });
	}
}
