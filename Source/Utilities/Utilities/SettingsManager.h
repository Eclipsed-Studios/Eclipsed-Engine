#pragma once

#include "BlackBoard.h"

namespace ENGINE_NAMESPACE
{
	class SettingsManager final
	{
	public:
		static void Load();
		static void Save();

	private:
		static inline Utilities::BlackBoard engineSettings;
		static inline Utilities::BlackBoard graphicsSettings;
	};
}