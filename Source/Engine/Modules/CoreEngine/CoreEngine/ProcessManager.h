#pragma once

#include <vector>

namespace Eclipse
{
	class ProcessManager final
	{
	public:
		ProcessManager();
		~ProcessManager();

		bool LaunchChildProcess(const wchar_t* executablePath, const wchar_t* args = L"");

	private:
		void* job;
		std::vector<void*> processes;
	};
}