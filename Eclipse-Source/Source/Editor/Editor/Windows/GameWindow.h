#pragma once

#include "Window.h"
#include "WindowBase.h"

#include "RenderingWindow.h"
#include "Math/Vector/Vector2.h"

namespace Eclipse::Editor
{
	class GameWindow final : public AbstractWindow, public BaseRenderingWindow
	{
		BASE_SELECTION(GameWindow, "Game")

	public:

		void Update() override;
		void Open() override;

	private:
		unsigned myGameFrameBuffer = 0;
		unsigned myGameTexture = 0;

		Math::Vector2i myLastWindowResolution = { 0, 0 };
	};
}