#include <iostream>

#include <AssetManagement/AssetEngine.h>
#include <ECS/ComponentManager.h>
#include <FMod/fmod.h>
#include <FMod/fmod.hpp>

#include <filesystem>


int main()
{
	FMOD::System* mySystem;

	FMOD_RESULT result;

	result = FMOD::System_Create(&mySystem);
	if (result != FMOD_OK)
	{
		return 1 ;
	}

	result = mySystem->init(512, FMOD_INIT_NORMAL, nullptr);
	if (result != FMOD_OK)
	{
		return 1;
	}

	FMOD::Sound* sound;
	FMOD::Channel* channel = nullptr;

	std::string filePath = "F:/Projects/Template/Bin/T.mp3";

	result = mySystem->createSound(filePath.c_str(), FMOD_DEFAULT, nullptr, &sound);
	result = mySystem->playSound(sound, nullptr, false, &channel);

	while (true)
	{
		mySystem->update();

		std::cout << "NOAH SUGER" << std::endl;
		std::cin;
	}
}