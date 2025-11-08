#pragma once

namespace Eclipse
{
	class GameCompiler
	{
	public:
		void CompileGame();

	private:
		void GenerateForcelink();
		void GenerateProject();
		void Compile();
	};
}