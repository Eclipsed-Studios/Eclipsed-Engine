#pragma once

#include "EclipsedRuntime/Editor/Windows/WindowBase.h"


namespace Eclipse::Editor
{
	class GameSettingsWindow final : public AbstractWindow
	{
		EDITOR_WINDOW_BASE_2(GameSettingsWindow, "Game Settings", "Settings");

	public:
		void Update() override;

	private:
		void DrawSceneEditor();
		void DrawCollisionLayerEditor();
		void SaveLayerEditToJSON();
	};
}