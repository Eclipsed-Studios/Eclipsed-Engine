#pragma once

#include "WindowBase.h"
#include "RenderingWindow.h"

#include "Math/Vector/Vector2.h"

namespace Eclipse::Editor
{
	class SceneWindow final : public AbstractWindow, public BaseRenderingWindow
	{
		BASE_SELECTION(SceneWindow, "Scene")

	public:

		void MoveCamera();

		void Update() override;
		void Open() override;

	private:
		unsigned mySceneFrameBuffer = 0;
		unsigned mySceneTexture = 0;

		Math::Vector2i myLastWindowResolution = { 0, 0 };

		Math::Vector2f myInspectorPosition = {0, 0};
		float myInspectorRotation = 0;
		Math::Vector2f myInspectorScale = {1, 1};
	};
}