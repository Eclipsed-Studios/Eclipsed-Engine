#pragma once

#include <string>
#include <unordered_map>

#include "Input/Input.h"
#include "EclipsedEngine/Components/Component.h"

class TutorialPart
{
public:
	std::string description;

	Eclipse::Keycode::Scancode code;
	bool listenToKey;

	std::string eventName;
	bool listenToEvent;

	bool freezePlayer;
	bool completed;
};

class Tutorial
{
public:
	static void Update();
	static void StartTutorial(std::string name);
	static void DisableTempTutorial();

	static void CompletedTutorialPart();

	static TutorialPart& GetCurrentTutorial();

	static bool HasActiveTutorial();

private:
	static inline std::unordered_map<std::string, TutorialPart> tutorials = 
	{
		{"tutorial-interact", { "Press [E] to interact.", Eclipse::Keycode::Scancode::E, true, "", false, true, false}},

	};

	static inline std::string activeTutorial;
};

