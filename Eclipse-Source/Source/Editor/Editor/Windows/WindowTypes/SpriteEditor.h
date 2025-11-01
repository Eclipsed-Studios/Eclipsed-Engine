#ifdef ECLIPSED_EDITOR
#pragma once

#include "Editor/Windows/WindowBase.h"

#include "RenderingWindow.h"

#include "Utilities/Math/Vector/Vector2.h"

#include "CoreEngine/AssetManagement/Resources.h"
#include "CoreEngine/AssetManagement/Resources/Texture.h"

#include "Utilities/Math/RectSizePos.h"
#include "AssetEngine/Assets/Texture.h"

namespace Eclipse::Editor
{
	class SpriteEditor final : public AbstractWindow
	{
		EDITOR_WINDOW_BASE_2(SpriteEditor, "Sprite")

	public:

		void Update() override;
		void Open() override;

		static void SetTexture(const char* aPath);

	private:
		static void Save(const char* relativePath);
		static void Load(const char* relativePath);

		void EdgeScaling();

		void ScrollManager();
		void MouseManager();

		void DrawRects();
		void RectProperties();

		bool IsInPropertyWindow();
		bool CheckIfRectMove(Math::Vector2f aOffsetPositionScaledRight);

		bool RectangleEdgeChoosing(Math::Vector2f aMousePosition);
		void ChangeEdgeCursor(Math::Vector2f aMousePosition);

	private:
		Math::Vector2f myInspectorPosition = { 0, 0 };
		Math::Vector2f myLastInspectorPosition = { 0, 0 };
		Math::Vector2f myInspectorScale = { 1, 1 };

		Math::Vector2f myInspectorPositionOffsetFromZeroZero = { 0, 0 };
		Math::Vector2f mySaveMin = { 0, 0 };

	private:
		static inline Math::Vector2f mySpriteScaleSnapping;

	private:
		Math::Vector2f myWindowSize;
		Math::Vector2f myLastWindowResolution = { 0, 0 };
		Math::Vector2f normalizedMousePosition = { 0, 0 };
		Math::Vector2i windowRelativeMousePosition = { 0, 0 };
		Math::Vector2f myStartCursorPosition = { 0, 0 };

		ImVec2 myPropertyWindowPosition = { 0, 0 };
		ImVec2 mySizeOfProperyWindow = { 0, 0 };

		Math::Vector4f backgroundColor = { 0.7f, 0.7f, 0.7f, 1.f };

		static inline Math::Vector2i myTextureSize;
		float myTextureSizeAspectRatio = 0;

	private:
		bool holdingRect = false;

		float totalYScroll = 0;
		float lastScroll = 0;
		bool mouseIsDown = false;
		bool mouseIsDownLeft = false;

		Math::Vector2f mySpriteCurrentMin;
		Math::Vector2f mySpriteCurrentMax;

		float currentPositioningX = 0.f;
		float currentScalingX = 0.f;
		float* myScaleEdgeScalingX = nullptr;
		float* myPositionEdgeScalingX = nullptr;

		float currentPositioningY = 0.f;
		float currentScalingY = 0.f;
		float* myScaleEdgeScalingY = nullptr;
		float* myPositionEdgeScalingY = nullptr;

		float myMinEdgeScaling;
		float myMaxEdgeScaling;

		float mouseEdgeSensetivity = 5;

	private:
		static inline Textures myTexture;
		static inline bool textureSet;
		static inline std::string activeRelativePath;


		struct Rect
		{
			Math::RectSizePos rect;

			std::string name;
			bool isSelected = false;
		};


		Math::Vector2f cursorPosBeforeImage = { 0, 0 };

		Rect myCopiedRectInfo;

		Rect* mySelectedRectPtr = nullptr;
		Math::Vector2f savedPositionBeforeMove;
		static inline std::vector<Rect> myRects;
	};
}
#endif