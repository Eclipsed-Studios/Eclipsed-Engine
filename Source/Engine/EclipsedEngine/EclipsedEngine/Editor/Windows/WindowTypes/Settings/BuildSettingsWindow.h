#pragma once

#ifdef ECLIPSED_EDITOR

#include "EclipsedEngine/Editor/Windows/WindowBase.h"

namespace Eclipse::Editor
{
	class BuildSettingsWindow : public AbstractWindow
	{
		EDITOR_WINDOW_BASE_3(BuildSettingsWindow, "Build", "Settings");

	public:
		void Update() override;

	private:
		void CleanBuild();
		void Build();

	private:
#ifdef _DEBUG
		static inline const bool isDebugBuild = true;
#else
		static inline const bool isDebugBuild = false;
#endif
		static inline bool enableNetworking = false;
		static inline bool enableSteamSdk = false;
		static inline bool enableDiscordSdk = false;
	};
}

#endif