#pragma once

#include "BlackBoard.h"

namespace ENGINE_NAMESPACE
{
	class SettingsManager final
	{
	public:
		static void Load();
		static void Save();

		static Utilities::BlackBoard& GetSettings();

	private:
		static inline Utilities::BlackBoard settings;
	};
}