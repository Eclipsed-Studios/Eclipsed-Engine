#pragma once
#include "CoreEngine/Math/Vector/Vector2.h"
namespace Eclipse::Configs
{
	class BuildSettings {
		static inline const char* name = "Game Name";
		static inline const bool enableSteamSdk = false;
		static inline const bool enableDiscordSdk = false;
		static inline const bool enableNetworking = false;
		static inline const char* simon = "noah";
		static inline const Math::Vector2f gravity = { 0.000000f, -9.820000f };;
	};
}
