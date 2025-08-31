#pragma once

namespace ENGINE_NAMESPACE
{
	class Engine
	{
	public:
		Engine() = delete;
		~Engine() = delete;

	public:
		static void Init();
		
		static bool Begin();
		static void Update();
		static void End();
	};
}