#pragma once

namespace Eclipse
{
	class EclipsedEngine
	{
	public:
		void StartEngine();
		
		void Update();
		
	private:
		void Internal_BeginFrame();
		void Internal_Update();
		void Internal_EndFrame();

	};
}
