#include "ProcessManager.h"

#include <Windows.h>

namespace Eclipse
{
	ProcessManager::ProcessManager()
	{
        job = CreateJobObjectW(NULL, L"eclipsed_game_enginge_job");
        if (!job) 
        {
            assert("Failed to create job object.");
            return;
        }

        JOBOBJECT_EXTENDED_LIMIT_INFORMATION jeli = { 0 };
        jeli.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;

        if (!SetInformationJobObject(job, JobObjectExtendedLimitInformation, &jeli, sizeof(jeli))) 
        {
            assert("Failed to configure job.");

            CloseHandle(job);
            job = NULL;
        }
	}

	ProcessManager::~ProcessManager()
	{

	}

    bool ProcessManager::LaunchChildProcess(const wchar_t* executablePath, const wchar_t* args)
    {
        if (!job) 
        {
            assert("Job object is not available.");
            return false;
        }

        std::wstring cmdLine = executablePath;
        if (args)
        {
            cmdLine += L" ";
            cmdLine += args;
        }

        STARTUPINFOW si = { sizeof(si) };
        PROCESS_INFORMATION pi = { 0 };

        std::vector<wchar_t> cmdBuffer(cmdLine.begin(), cmdLine.end());
        cmdBuffer.push_back(L'\0');

        if (!CreateProcessW(NULL, cmdBuffer.data(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
        {
            assert("Failed to launch application.");
            return false;
        }

        if (!AssignProcessToJobObject(job, pi.hProcess))
        {
            assert("Failed to assign process to job.");
            return false;
        }

        processes.push_back(pi.hProcess);
        CloseHandle(pi.hThread);

        return true;
    }
}