#pragma once

#include "WindowBase.h"

namespace ENGINE_NAMESPACE::Editor
{
	class GameSettingsWindow final : public AbstractWindow
	{
		BASE_SELECTION(GameSettingsWindow, "Game Settings", "Settings")

	public:
		void Update() override;

	private:
		void DrawCollisionLayerEditor();
		void SaveLayerEditToJSON();
	};
}