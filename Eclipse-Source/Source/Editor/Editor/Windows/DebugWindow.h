#pragma once

#include "WindowBase.h"

#include <vector>
#include <queue>
#include <list>


namespace Eclipse::Editor
{
	class DebugWindow final : public AbstractWindow 
	{
		BASE_SELECTION(DebugWindow, "Profiler", "Debug")

	public:
		void Open() override;

		void PreUpdate() override;
		void Update() override;
		void PostUpdate() override;

	private:
		int totalPhysMem;
		int totalVirtMem;
		int PhysMemUsed;
		int VirtuMemUsed;

		const int Max_Entries = 100'000;
		int CurrentIndex = 0;
		std::vector<float> X = std::vector<float>(Max_Entries);
		std::vector<float> Time = std::vector<float>(Max_Entries);
		std::vector<float> virtualMemoryCounter = std::vector<float>(Max_Entries);
		std::vector<float> physicalMemoryCounter = std::vector<float>(Max_Entries);
	};
}