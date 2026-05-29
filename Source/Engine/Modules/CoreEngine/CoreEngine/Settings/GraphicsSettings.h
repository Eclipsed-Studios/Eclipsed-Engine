#pragma once

#include "SettingsBase.hpp"
#include "CoreEngine/Math/Vector/Vector2.h"

namespace Eclipse::Settings
{
	struct GraphicsSettings : public BaseSettings<GraphicsSettings>
	{
		SETTINGS_DATA{
			Math::Vector2<int> Resolution = { 1280, 720 };
			bool Fullscreen = false;
			int NumberOfRenderBuffers = 0;

			SERIALIZE(
				MAKE_NVP(Resolution),
				MAKE_NVP(Fullscreen),
				MAKE_NVP(NumberOfRenderBuffers)
				)
		};

		static const decltype(Data::Resolution)& GetResolution() {
			return GetData().Resolution;
		} static void SetResolution(const decltype(Data::Resolution)& data) {
			GetData().Resolution = data;
		}
		GET_SET(Fullscreen)
		GET_SET(NumberOfRenderBuffers)

		BASE_SETTINGS(GraphicsSettings, "graphics");
	};
}