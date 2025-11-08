#include "GameCompiler.h"

void Eclipse::GameCompiler::CompileGame()
{
	GenerateForcelink();
}

void Eclipse::GameCompiler::GenerateForcelink()
{
	const std::filesystem::path& projectRoot = PathManager::GetProjectRoot();
	const std::filesystem::path& source = projectRoot / "Source";
}

void Eclipse::GameCompiler::GenerateProject()
{
}

void Eclipse::GameCompiler::Compile()
{
}
