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
		void Build();

	private:
		static inline bool isDebugBuild = false;
		static inline bool enableNetworking = false;
		static inline bool enableSteamApi = false;
	};
}

#endif