#pragma once

#include <vector>
#include <string>

#include "SettingsBase.hpp"
#include "EclipsedEngine/Core/Math/Vector/Vector2.h"

namespace Eclipse::Settings
{
	struct EditorSettings final : public BaseSettings<EditorSettings>
	{
		SETTINGS_DATA{
			std::string LastActiveScene = "";
			bool OpenLastOpenSceneOnStartup = true;

			SERIALIZE(
				MAKE_NVP(LastActiveScene),
				MAKE_NVP(OpenLastOpenSceneOnStartup)
			)
		};

		GET_SET(LastActiveScene);
		GET_SET(OpenLastOpenSceneOnStartup);

		BASE_SETTINGS(EditorSettings, "editor")
	};
}