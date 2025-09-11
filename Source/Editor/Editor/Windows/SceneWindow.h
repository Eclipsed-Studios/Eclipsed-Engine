#pragma once

#include "WindowBase.h"

#include "Math/Vector/Vector2.h"

namespace Eclipse::Editor
{
	class SceneWindow final : public AbstractWindow
	{
		BASE_SELECTION(SceneWindow, "Scene")

	public:

		void Update() override;
		void Open() override;

	private:
		unsigned mySceneFrameBuffer = 0;
		unsigned mySceneTexture = 0;

		Math::Vector2i myLastWindowResolution = { 0, 0 };
	};
}