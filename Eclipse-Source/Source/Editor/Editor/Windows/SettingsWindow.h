#pragma once

#include "WindowBase.h"

namespace Eclipse::Editor
{
	class GameSettingsWindow final : public AbstractWindow
	{
		BASE_SELECTION(GameSettingsWindow, "Game Settings", "Settings")

	public:
		void Update() override;

	private:
		void DrawSceneEditor();
		void DrawCollisionLayerEditor();
		void SaveLayerEditToJSON();
	};
}