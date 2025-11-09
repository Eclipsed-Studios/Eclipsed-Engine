#pragma once

namespace Eclipse
{
	class GameCompiler
	{
	public:
		static void CompileGame();

	private:
		static void GenerateForcelink();
		static void GenerateProject();
		static void Compile();

	private:
		static inline bool GameIsCompiling = false;

	public:
		static inline int timesCalled = 0;
	};
}