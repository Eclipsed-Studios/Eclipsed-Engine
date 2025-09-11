#pragma once

namespace Eclipse
{
	class DebugInformationCollector final
	{
	public:
		static int GetRenderCalls();

		static void UpdateRenderCalls(int amount = 1);
		static void ResetRenderCalls();

	private:
		static inline int renderCalls = 0;
	};
}