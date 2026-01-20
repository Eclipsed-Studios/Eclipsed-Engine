#pragma once

#include "SettingsBase.hpp"

namespace Eclipse::Settings
{
	struct EngineSettings : public BaseSettings<EngineSettings>
	{
		SETTINGS_DATA{
			int test = 0;

			SERIALIZE(MAKE_NVP(test))
		};

		BASE_SETTINGS(EngineSettings, "TestSettings");
	};
}