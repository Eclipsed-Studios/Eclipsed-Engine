#ifdef _EDITOR
#pragma once

#include "WindowBase.h"
#include "RenderingWindow.h"

#include "Math/Vector/Vector2.h"

#include <vector>

namespace Eclipse
{
	class Component;

	namespace Editor
	{
		class SceneWindow final : public AbstractWindow, BaseRenderingWindow
		{
			BASE_SELECTION(SceneWindow, "Scene")

		public:

			void CopyManager();
			void PasteManager();

			void CopyPasteManager();

			void ObjectSnappingGizmo();

			void SpriteSelecter();

			void ZoomToObject();
			void ScrollManager();
			void MouseManager();
			void SpriteDragging();

			void Update() override;
			void Open() override;

			void InitSceneBuffer();
			void InitSelectedObjectShader();

		private:
			Math::Vector2f myInspectorPosition = { 0, 0 };
			float myInspectorRotation = 0;
			Math::Vector2f myInspectorScale = { 1, 1 };

		private:
			Math::Vector2f myWindowSize;
			Math::Vector2f myLastWindowResolution = { 0, 0 };
			Math::Vector2f normalizedMousePosition = { 0, 0 };
			Math::Vector2ui windowRelativeMousePosition = { 0, 0 };

		private:
			Math::Vector2f mySpriteMouseDownPosition = { 0, 0 };
			Math::Vector2f mySpriteMoveVector = { 0, 0 };

		private:
			SpriteRenderer2D* mySelectedObject = nullptr;
			unsigned mySelectedSpriteHighlightProgram;

		private:
			std::vector<std::vector<Component*>> myCopiedComponentsFromObjects;

		private:
			bool myIsSnapping = false;
			float mySnappingDistance = 0.01f;

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
}
#endif