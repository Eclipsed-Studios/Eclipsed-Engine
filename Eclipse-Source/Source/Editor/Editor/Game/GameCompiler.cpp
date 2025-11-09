#include "GameCompiler.h"

namespace Eclipse
{
	void GameCompiler::CompileGame()
	{
		Compile();
	}

	void GameCompiler::GenerateForcelink()
	{
		const std::filesystem::path& projectRoot = PathManager::GetProjectRoot();
		const std::filesystem::path& source = projectRoot / "Source";
	}

	void GameCompiler::GenerateProject()
	{
	}

	void GameCompiler::Compile()
	{
		// cmake -G "Visual Studio 17 2022" -T host=x64 -S . -B build
		std::string sourceDir = PathManager::GetProjectRoot().generic_string();
		std::string buildDir = (PathManager::GetProjectRoot() / "build").generic_string();
		std::string targetDir = (PathManager::GetProjectRoot() / "Cache").generic_string();
		
		std::string buildCmakeCommand = "cd /d \"" + sourceDir + "\" && cmake -G \"Visual Studio 17 2022\" -T host=x64 -S . -B build";
		std::system(buildCmakeCommand.c_str());

		std::string buildDLLCommand = "cd /d \"" + buildDir + "\" && cmake --build .";
		std::system(buildDLLCommand.c_str());

		timesCalled++;
	}
}