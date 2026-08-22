#include "TestGameComponent.h"

#include "Core/Timer.h"

void TestGameComponent::Update()
{
	values = Eclipse::Core::Timer::GetDeltaTime();
	totalTime = Eclipse::Core::Timer::GetTotalTime();
}
