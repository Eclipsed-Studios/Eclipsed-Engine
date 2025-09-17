#pragma once

#include "WindowBase.h"
#include "RenderingWindow.h"

#include "Math/Vector/Vector2.h"

namespace Eclipse::Editor
{
	class SceneWindow final : public AbstractWindow, BaseRenderingWindow
	{
		BASE_SELECTION(SceneWindow, "Scene")

	public:

		void PixelPickCheck();

		void ZoomToObject();
		void ScrollManager();
		void MouseManager();

		void Update() override;
		void Open() override;

		void InitSceneBuffers();

	private:
		Math::Vector2f myInspectorPosition = { 0, 0 };
		float myInspectorRotation = 0;
		Math::Vector2f myInspectorScale = { 1, 1 };

	private:
		Math::Vector2i myLastWindowResolution = { 0, 0 };
		Math::Vector2f normalizedMousePosition = { 0, 0 };
		Math::Vector2ui windowRelativeMousePosition = { 0, 0 };

	private:
		float totalYScroll = 0;
		float lastScroll = 0;
		bool mouseIsDown = false;

		
		bool draggingSprite = false;

	private:
		unsigned mySceneFrameBuffer = 0;
		unsigned mySceneTexture = 0;
	};
}