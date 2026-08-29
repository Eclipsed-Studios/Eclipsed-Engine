#include "Tutorial.h"

#include "Core/Timer.h"

#include "ECS/GameObject.h"
#include "EclipsedEngine/Components/Transform2D.h"
#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"
#include "EclipsedEngine/Components/Audio/AudioEmitter.h"

#include "Core/EventSystem/EventSystem.h"


#include "EclipsedEngine/Components/UI/TextRenderer.h"

#include "TutorialStarter.h"

void TutorialComp::Start()
{
	textRenderer = gameObject->GetComponent<Eclipse::TextRenderer>();
}

void TutorialComp::Update()
{
	Tutorial::Update();

	if (!Tutorial::HasActiveTutorial())
	{
		textRenderer->myText = "";

		return;
	}

	TutorialPart& part = Tutorial::GetCurrentTutorial();
	textRenderer->myText = part.description;
}
