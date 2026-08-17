#pragma once

#include "EclipsedEngine.Core.hpp"




namespace Eclipse
{
	class ECL_API Engine
	{
	public:
		void Test();
		void BeginFrame();
		void EndFrame();
		void Render();
		bool ShouldClose();
	};
}