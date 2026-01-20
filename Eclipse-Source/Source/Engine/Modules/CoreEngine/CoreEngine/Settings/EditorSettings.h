#pragma once

#include "SettingsBase.hpp"
#include "CoreEngine/Math/Vector/Vector2.h"

namespace Eclipse::Settings
{
	struct EditorSettings : public BaseSettings<EditorSettings>
	{
		SETTINGS_DATA{
			std::string LastActiveScene = "";

			SERIALIZE(
				MAKE_NVP(LastActiveScene)
			)
		};

		GET_SET(LastActiveScene)

		BASE_SETTINGS(EditorSettings, "editor");
	};
}