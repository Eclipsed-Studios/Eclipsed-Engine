#pragma once

#include <vector>
#include <string>

#include "SettingsBase.hpp"
#include "CoreEngine/Math/Vector/Vector2.h"

#include <array>

namespace Eclipse::Settings
{
	struct PhysicsSettings : public BaseSettings<PhysicsSettings>
	{
		#define MAX_LAYERS 16

		SETTINGS_DATA{
		std::array<unsigned long long, MAX_LAYERS> PhysicsLayers;

			SERIALIZE(
				MAKE_NVP(PhysicsLayers)
			)
		};

		GET_SET(PhysicsLayers)

		BASE_SETTINGS(PhysicsSettings, "physics");
	};
}