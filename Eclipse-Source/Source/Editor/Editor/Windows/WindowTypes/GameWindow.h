#pragma once

#include "Window.h"
#include "Editor/Windows/WindowBase.h"


#include "RenderingWindow.h"
#include "Math/Vector/Vector2.h"

namespace Eclipse::Editor
{
	class GameWindow final : public AbstractWindow, public BaseRenderingWindow
	{
		BASE_SELECTION(GameWindow, "Game")

	public:

		void UpdateFreeAspect();
		void UpdateSpecifiedRes();

		void Update() override;
		void Open() override;

	private:
		unsigned myGameFrameBuffer = 0;
		unsigned myGameTexture = 0;

		Math::Vector2i myLastWindowResolution = { 0, 0 };

		enum WindowMode
		{
			FreeAspect,
			AnythingElse
		} myCurrentWindowMode;

		int currentResIndex = 1;

		Math::Vector2f myWindowResAspect = {1.7777f, 0.5625f};

		float menuHeight = 0;
	};
}