#include "Tutorial.h"

#include "Core/Timer.h"

#include "ECS/GameObject.h"
#include "EclipsedEngine/Components/Transform2D.h"
#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"
#include "EclipsedEngine/Components/Audio/AudioEmitter.h"

#include "Core/EventSystem/EventSystem.h"

void Tutorial::Update()
{
	if (activeTutorial.empty()) return;

	TutorialPart& tut = tutorials[activeTutorial];
	if (tut.listenToKey)
	{
		if (Eclipse::Input::GetKeyDown(tut.code))
		{
			tut.completed = true;
			activeTutorial = "";
		}
	}
}

void Tutorial::StartTutorial(std::string name)
{
	TutorialPart& tut = tutorials[name];
	if (tut.completed) return;

	activeTutorial = name;

	if (tut.listenToEvent)
	{
		Eclipse::EventSystem::Subscribe(tut.eventName, Tutorial::CompletedTutorialPart);
	}
}

void Tutorial::DisableTempTutorial()
{
	activeTutorial = "";
}

void Tutorial::CompletedTutorialPart()
{
	TutorialPart& tut = tutorials[activeTutorial];
	Eclipse::EventSystem::Unsubscribe(Tutorial::CompletedTutorialPart);
	tut.completed = true;
	activeTutorial = "";
}

TutorialPart& Tutorial::GetCurrentTutorial()
{
	return tutorials[activeTutorial];
}

bool Tutorial::HasActiveTutorial()
{
	return !activeTutorial.empty();
}
