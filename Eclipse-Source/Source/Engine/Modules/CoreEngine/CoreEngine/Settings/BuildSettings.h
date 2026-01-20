#pragma once

#include "SettingsBase.hpp"
#include "CoreEngine/Math/Vector/Vector2.h"

namespace Eclipse::Settings
{
	struct BuildSettings : public BaseSettings<BuildSettings>
	{
		SETTINGS_DATA{
			Math::Vector2<int> Resolution;

			SERIALIZE(MAKE_NVP(Resolution))
		};

		BASE_SETTINGS(BuildSettings, "BuildSettings.json");
	};
}