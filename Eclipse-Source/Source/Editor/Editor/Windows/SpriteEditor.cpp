#define _EDITOR

#ifdef _EDITOR
#include "SpriteEditor.h"

#include "ImGui/imgui.h"
#include "PhysicsEngine.h"
#include "PhysicsEngineSettings.h"

#include "Math/Math.h"

#include "Input/Input.h"

#include "AssetManagement/Resources.h"

#include <iostream>

#include <sstream>

#undef min

namespace Eclipse::Editor
{
	void SpriteEditor::ScrollManager()
	{
		ImGuiIO& io = ImGui::GetIO();
		float deltaYScroll = io.MouseWheel;

		if (deltaYScroll == 0.0f)
			return;

		float textureSizeScaleFactor = static_cast<float>(std::min(myTextureSize.x, myTextureSize.y)) * 0.001f;

		float baseFactor = 1.07f * textureSizeScaleFactor;
		if (Input::GetKey(Keycode::L_SHIFT))
			baseFactor = 1.3f * textureSizeScaleFactor;

		float scaleMagnitude = std::log2(myInspectorScale.x + 1.0f);
		float dynamicFactor = baseFactor - (0.02f * scaleMagnitude);

		dynamicFactor = std::max(1.001f, dynamicFactor);
		float zoomFactor = (deltaYScroll > 0) ? dynamicFactor : 1.0f / dynamicFactor;

		Math::Vector2f zoomCenter = normalizedMousePosition + myInspectorPosition;

		//myInspectorPosition = zoomCenter + (myInspectorPosition - zoomCenter) * (1.0f / zoomFactor);

		myInspectorScale *= { zoomFactor, zoomFactor };
	}

	bool SpriteEditor::IsInPropertyWindow()
	{
		if (windowRelativeMousePosition.x > myPropertyWindowPosition.x + mySizeOfProperyWindow.x)
			return false;
		if (windowRelativeMousePosition.x < myPropertyWindowPosition.x)
			return false;
		if (windowRelativeMousePosition.y > myPropertyWindowPosition.y + mySizeOfProperyWindow.y)
			return false;
		if (windowRelativeMousePosition.y < myPropertyWindowPosition.y)
			return false;

		return true;
	}

	bool SpriteEditor::CheckIfRectMove(Math::Vector2f aOffsetPositionScaledRight)
	{
		auto& rect = *mySelectedRectPtr;

		if (aOffsetPositionScaledRight.x > rect.position.x + rect.size.x)
			return false;
		if (aOffsetPositionScaledRight.x < rect.position.x)
			return false;
		if (aOffsetPositionScaledRight.y > rect.position.y + rect.size.y)
			return false;
		if (aOffsetPositionScaledRight.y < rect.position.y)
			return false;

		savedPositionBeforeMove = rect.position;
		return true;
	}

	void SpriteEditor::MouseManager()
	{
		if (myLastInspectorPosition.x != myInspectorPosition.x || myLastInspectorPosition.y != myInspectorPosition.y)
		{
			myLastInspectorPosition = myInspectorPosition;

			mySpriteCurrentMin = { std::clamp(static_cast<float>(-myInspectorPosition.x + myInspectorPositionOffsetFromZeroZero.x), -myInspectorPosition.x, -myInspectorPosition.x + myTextureSize.x), std::clamp(static_cast<float>(myInspectorPosition.y + myInspectorPositionOffsetFromZeroZero.y), myInspectorPosition.y, myInspectorPosition.y + myTextureSize.y) };

			// mySpriteCurrentMin.x = roundf(mySpriteCurrentMin.x / (mySpriteScaleSnapping.x * myInspectorScale.x)) * mySpriteScaleSnapping.x * myInspectorScale.x;
			// mySpriteCurrentMin.y = roundf(mySpriteCurrentMin.y / (mySpriteScaleSnapping.y * myInspectorScale.y)) * mySpriteScaleSnapping.y * myInspectorScale.y;
		}


		{
			ImVec2 mousePos = ImGui::GetMousePos();
			ImGui::SetCursorPos(ImVec2(0, 0));
			ImVec2 cursorScreenPos = ImGui::GetCursorScreenPos();

			windowRelativeMousePosition = { static_cast<int>((mousePos.x - cursorScreenPos.x)), static_cast<int>(mousePos.y - cursorScreenPos.y) };

			normalizedMousePosition.x = windowRelativeMousePosition.x / myWindowSize.x;
			normalizedMousePosition.y = windowRelativeMousePosition.y / myWindowSize.y;

			normalizedMousePosition.x = normalizedMousePosition.x * 2.f - 1;
			normalizedMousePosition.y = normalizedMousePosition.y * 2.f - 1;
		}

		if (myPositionEdgeScalingX)
		{
			float mouseDragDelta = ImGui::GetMouseDragDelta().x / myInspectorScale.x;
			float positionSnappingX = roundf(mouseDragDelta);
			float newPosition = currentPositioningX + positionSnappingX;
			float clampedPosition = std::clamp(newPosition, 0.f, mySelectedRectPtr->position.x + mySelectedRectPtr->size.x);
			float effectiveDelta = clampedPosition - currentPositioningX;

			(*myPositionEdgeScalingX) = clampedPosition;
			mySelectedRectPtr->size.x = currentScalingX - effectiveDelta;
		}
		else if (myScaleEdgeScalingX)
		{
			float mouseDragDelta = ImGui::GetMouseDragDelta().x / myInspectorScale.x;
			float positionSnappingX = roundf(mouseDragDelta);
			(*myScaleEdgeScalingX) = currentScalingX + positionSnappingX;
			(*myScaleEdgeScalingX) = std::clamp((*myScaleEdgeScalingX), 0.f, myTextureSize.x - mySelectedRectPtr->position.x);
		}
		if (myPositionEdgeScalingY)
		{
			float mouseDragDelta = ImGui::GetMouseDragDelta().y / myInspectorScale.x;
			float positionSnappingY = roundf(mouseDragDelta);

			float newPosition = currentPositioningY + positionSnappingY;
			float clampedPosition = std::clamp(newPosition, 0.f, mySelectedRectPtr->position.y + mySelectedRectPtr->size.y);
			float effectiveDelta = clampedPosition - currentPositioningY;

			(*myPositionEdgeScalingY) = clampedPosition;
			mySelectedRectPtr->size.y = currentScalingY - effectiveDelta;
		}
		else if (myScaleEdgeScalingY)
		{
			float mouseDragDelta = ImGui::GetMouseDragDelta().y / myInspectorScale.x;
			float positionSnappingY = roundf(mouseDragDelta);
			(*myScaleEdgeScalingY) = currentScalingY + positionSnappingY;
			(*myScaleEdgeScalingY) = std::clamp((*myScaleEdgeScalingY), 0.f, myTextureSize.y - mySelectedRectPtr->position.y);
		}

		if (ImGui::IsMouseReleased(0))
		{
			myPositionEdgeScalingX = nullptr;
			myPositionEdgeScalingY = nullptr;
			myScaleEdgeScalingX = nullptr;
			myScaleEdgeScalingY = nullptr;
		}

		if (ImGui::IsWindowHovered())
		{
			myInspectorPositionOffsetFromZeroZero = { static_cast<float>(myInspectorPosition.x + windowRelativeMousePosition.x), static_cast<float>(-myInspectorPosition.y + windowRelativeMousePosition.y) };

			Math::Vector2f OffsetPositionScaledRight;
			OffsetPositionScaledRight.x = myInspectorPositionOffsetFromZeroZero.x / myInspectorScale.x;
			OffsetPositionScaledRight.y = myInspectorPositionOffsetFromZeroZero.y / myInspectorScale.y;

			ChangeEdgeCursor(OffsetPositionScaledRight);

			if (ImGui::IsMouseClicked(0))
			{
				if (!RectangleEdgeScaling(OffsetPositionScaledRight))
				{
					bool createNewRect = true;
					bool propertyWindowSelected = IsInPropertyWindow();

					if (!propertyWindowSelected)
					{
						bool clickedSelectedRect = false;
						if (mySelectedRectPtr)
						{
							clickedSelectedRect = CheckIfRectMove(OffsetPositionScaledRight);

							if (clickedSelectedRect)
								holdingRect = true;
							else
								holdingRect = false;
						}

						if (!clickedSelectedRect)
						{
							mySelectedRectPtr = nullptr;
							for (auto& rect : myRects)
							{
								if (OffsetPositionScaledRight.x > rect.position.x + rect.size.x)
									continue;
								if (OffsetPositionScaledRight.x < rect.position.x)
									continue;
								if (OffsetPositionScaledRight.y > rect.position.y + rect.size.y)
									continue;
								if (OffsetPositionScaledRight.y < rect.position.y)
									continue;

								createNewRect = false;
								mySelectedRectPtr = &rect;

								rect.isSelected = true;

								break;
							}

							if (createNewRect)
							{
								mouseIsDownLeft = true;

								float posX = static_cast<float>(myInspectorPositionOffsetFromZeroZero.x);
								float posY = static_cast<float>(myInspectorPositionOffsetFromZeroZero.y);

								float positionSnappingX = roundf(posX / (mySpriteScaleSnapping.x * myInspectorScale.x)) * mySpriteScaleSnapping.x * myInspectorScale.x;
								float positionSnappingY = roundf(posY / (mySpriteScaleSnapping.y * myInspectorScale.y)) * mySpriteScaleSnapping.y * myInspectorScale.y;

								float spriteCurrentMinX = std::clamp(static_cast<float>(-myInspectorPosition.x + positionSnappingX), -myInspectorPosition.x, -myInspectorPosition.x + myTextureSize.x * myInspectorScale.x);
								float spriteCurrentMinY = std::clamp(static_cast<float>(myInspectorPosition.y + positionSnappingY), myInspectorPosition.y, myInspectorPosition.y + myTextureSize.y * myInspectorScale.y);

								float inspectorPosX = roundf(myInspectorPosition.x / (mySpriteScaleSnapping.x * myInspectorScale.x)) * mySpriteScaleSnapping.x * myInspectorScale.x;
								float inspectorPosY = roundf(myInspectorPosition.y / (mySpriteScaleSnapping.y * myInspectorScale.y)) * mySpriteScaleSnapping.y * myInspectorScale.y;

								myInspectorPositionOffsetFromZeroZero.x = spriteCurrentMinX + inspectorPosX;
								myInspectorPositionOffsetFromZeroZero.y = spriteCurrentMinY - inspectorPosY;

								float clampedSaveMinX = std::clamp(static_cast<float>(positionSnappingX), 0.f, static_cast<float>(myTextureSize.x) * myInspectorScale.x);
								float clampedSaveMinY = std::clamp(static_cast<float>(positionSnappingY), 0.f, static_cast<float>(myTextureSize.y) * myInspectorScale.y);


								mySaveMin.x = clampedSaveMinX;
								mySaveMin.y = clampedSaveMinY;

								mySpriteCurrentMin = { spriteCurrentMinX,  spriteCurrentMinY };
							}
						}

						if (!ImGui::IsKeyDown(ImGuiKey_LeftShift))
						{
							for (auto& rect : myRects)
							{
								rect.isSelected = false;
							}

							if (mySelectedRectPtr)
								mySelectedRectPtr->isSelected = true;
						}
					}
				}
			}

			if ((ImGui::IsMouseDown(1) || ImGui::IsMouseDown(2)))
				mouseIsDown = true;

			ScrollManager();

			if (ImGui::IsMouseReleased(0))
			{
				holdingRect = false;

				if (mouseIsDownLeft)
				{
					Math::Vector2f size = mySpriteCurrentMax - mySpriteCurrentMin;

					float sizeDivScaleX = size.x / myInspectorScale.x;
					float sizeDivScaleY = size.y / myInspectorScale.y;

					bool createRect = true;
					if (sizeDivScaleX <= 0)
						createRect = false;
					if (sizeDivScaleY <= 0)
						createRect = false;

					if (createRect)
					{
						float inspectPosOffsetZeroX = mySaveMin.x / myInspectorScale.x;
						float inspectPosOffsetZeroY = mySaveMin.y / myInspectorScale.y;

						Rect rect;

						rect.position = { inspectPosOffsetZeroX, inspectPosOffsetZeroY };
						rect.size = { sizeDivScaleX, sizeDivScaleY };
						rect.isSelected = false;

						myRects.emplace_back(rect);
					}

					mouseIsDownLeft = false;
				}
			}
		}

		if (mouseIsDown)
		{
			ImGuiIO& io = ImGui::GetIO();
			ImVec2 mouseDelta = io.MouseDelta;

			float correctScaledWindowSizeY = myWindowSize.y;
			float SizeXRatio = myWindowSize.x * (myWindowSize.y / myWindowSize.x);

			Math::Vector2f mouseDragdelta = { mouseDelta.x, mouseDelta.y };
			myInspectorPosition -= Math::Vector2f(mouseDragdelta.x, -mouseDragdelta.y);

			GraphicsEngine::SetCursor(GraphicsEngine::MouseCursor::Grab);
		}

		if (!(ImGui::IsMouseDown(1) || ImGui::IsMouseDown(2)))
			mouseIsDown = false;

	}

	void SpriteEditor::DrawRects()
	{
		for (auto& rect : myRects)
		{
			Math::Vector2f position = rect.position;
			Math::Vector2f size = rect.size;

			position.x *= myInspectorScale.x;
			position.y *= myInspectorScale.y;

			size.x *= myInspectorScale.x;
			size.y *= myInspectorScale.y;

			Math::Vector2f max = { position.x + size.x, position.y + size.y };

			ImVec2 minRect = ImVec2(position.x + cursorPosBeforeImage.x - myInspectorPosition.x, position.y + cursorPosBeforeImage.y + myInspectorPosition.y);
			ImVec2 maxRect = ImVec2(max.x + cursorPosBeforeImage.x - myInspectorPosition.x, max.y + cursorPosBeforeImage.y + myInspectorPosition.y);

			ImU32 color;
			if (rect.isSelected)
				color = (ImU32)IM_COL32(0, 0, 200, 255);
			else
				color = (ImU32)IM_COL32(58, 128, 236, 255);

			ImGui::GetWindowDrawList()->AddRect(minRect, maxRect, color);
		}
	}

	void SpriteEditor::RectProperties()
	{
		if (!mySelectedRectPtr)
			return;

		ImVec2 windowSize = ImGui::GetWindowSize();

		ImVec2 windowPosition = ImGui::GetWindowPos();

		ImVec2 positionToPlacePropertyWindow = { myStartCursorPosition.x + windowPosition.x, myStartCursorPosition.y + windowPosition.y + 30.f };
		ImVec2 sizeOfProperyWindow = { myStartCursorPosition.x + windowPosition.x + 200.f, myStartCursorPosition.y + windowPosition.y + 200.f };

		myPropertyWindowPosition = ImVec2(myStartCursorPosition.x + 5.f, myStartCursorPosition.y + 35.f);
		mySizeOfProperyWindow = { 200.f, 200.f };

		ImGui::GetWindowDrawList()->AddRectFilled(positionToPlacePropertyWindow, sizeOfProperyWindow, (ImColor)IM_COL32(100, 100, 100, 255), 2.f);

		ImGui::SetCursorPos(myPropertyWindowPosition);

		ImGui::Text("Position");
		ImGui::SetCursorPosX(myStartCursorPosition.x + 5.f);
		ImGui::Text("X:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(150.f);
		ImGui::DragFloat("##RectEditPositionX", &mySelectedRectPtr->position.x, 1.f, 0.f, myTextureSize.x - mySelectedRectPtr->size.x);
		ImGui::SetCursorPosX(myStartCursorPosition.x + 5.f);
		ImGui::Text("Y:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(150.f);
		ImGui::DragFloat("##RectEditPositionY", &mySelectedRectPtr->position.y, 1.f, 0.f, myTextureSize.y - mySelectedRectPtr->size.y);

		ImGui::SetCursorPosX(myStartCursorPosition.x + 5.f);
		ImGui::Text("Size");
		ImGui::SetCursorPosX(myStartCursorPosition.x + 5.f);
		ImGui::Text("X:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(150.f);
		ImGui::DragFloat("##RectEditSizeX", &mySelectedRectPtr->size.x, 1.f, 0.f, myTextureSize.x - mySelectedRectPtr->position.x);
		ImGui::SetCursorPosX(myStartCursorPosition.x + 5.f);
		ImGui::Text("Y:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(150.f);
		ImGui::DragFloat("##RectEditSizeY", &mySelectedRectPtr->size.y, 1.f, 0.f, myTextureSize.y - mySelectedRectPtr->position.y);
	}

	bool SpriteEditor::RectangleEdgeScaling(Math::Vector2f aMousePosition)
	{
		if (mySelectedRectPtr)
		{
			Rect& rect = *mySelectedRectPtr;

			Math::Vector2f min = rect.position;
			Math::Vector2f max = rect.position + rect.size;

			float edgeSens = mouseEdgeSensetivity / myInspectorScale.x;

			bool isInsideY = min.y - edgeSens * 0.5f < aMousePosition.y && max.y + edgeSens * 0.5f > aMousePosition.y;
			float distanceFromMaxX = abs(aMousePosition.x - max.x);
			if (distanceFromMaxX < edgeSens && isInsideY)
			{
				currentScalingX = rect.size.x;
				myScaleEdgeScalingX = &rect.size.x;
				myMinEdgeScaling = 0.f;
				myMaxEdgeScaling = static_cast<float>(myTextureSize.x) - rect.position.x;
			}
			float distanceFromMinX = abs(aMousePosition.x - min.x);
			if (distanceFromMinX < edgeSens && isInsideY)
			{
				currentPositioningX = rect.position.x;
				currentScalingX = rect.size.x;
				myPositionEdgeScalingX = &rect.position.x;
				myMinEdgeScaling = 0.f;
				myMaxEdgeScaling = rect.position.x + rect.size.x;
			}

			bool isInsideX = min.x - edgeSens * 0.5f < aMousePosition.x && max.x + edgeSens * 0.5f > aMousePosition.x;
			float distanceFromMaxY = abs(aMousePosition.y - max.y);
			if (distanceFromMaxY < edgeSens && isInsideX)
			{
				currentScalingY = rect.size.y;
				myScaleEdgeScalingY = &rect.size.y;
				myMinEdgeScaling = 0.f;
				myMaxEdgeScaling = static_cast<float>(myTextureSize.x) - rect.position.x;
			}
			float distanceFromMinY = abs(aMousePosition.y - min.y);
			if (distanceFromMinY < edgeSens && isInsideX)
			{
				currentPositioningY = rect.position.y;
				currentScalingY = rect.size.y;
				myPositionEdgeScalingY = &rect.position.y;
				myMinEdgeScaling = 0.f;
				myMaxEdgeScaling = rect.position.x + rect.size.x;
			}

			if (myPositionEdgeScalingX || myPositionEdgeScalingY || myScaleEdgeScalingX || myScaleEdgeScalingY)
			{
				return true;
			}

		}

		return false;
	}

	void SpriteEditor::ChangeEdgeCursor(Math::Vector2f aMousePosition)
	{
		if (mySelectedRectPtr)
		{
			bool rightEdge = false;
			bool leftEdge = false;
			bool upEdge = false;
			bool downEdge = false;
			
			Rect& rect = *mySelectedRectPtr;

			Math::Vector2f min = rect.position;
			Math::Vector2f max = rect.position + rect.size;

			float edgeSens = mouseEdgeSensetivity / myInspectorScale.x;

			bool isInsideY = min.y - edgeSens * 0.5f < aMousePosition.y && max.y + edgeSens * 0.5f > aMousePosition.y;
			float distanceFromMaxX = abs(aMousePosition.x - max.x);
			LOG(std::to_string(distanceFromMaxX));
			if (distanceFromMaxX < edgeSens && isInsideY)
			{
				rightEdge = true;
			}
			float distanceFromMinX = abs(aMousePosition.x - min.x);
			if (distanceFromMinX < edgeSens && isInsideY)
			{
				leftEdge = true;
			}

			bool isInsideX = min.x - edgeSens * 0.5f < aMousePosition.x && max.x + edgeSens * 0.5f > aMousePosition.x;
			float distanceFromMaxY = abs(aMousePosition.y - max.y);
			if (distanceFromMaxY < edgeSens && isInsideX)
			{
				upEdge = true;
			}
			float distanceFromMinY = abs(aMousePosition.y - min.y);
			if (distanceFromMinY < edgeSens && isInsideX)
			{
				downEdge = true;
			}

			if ((rightEdge && upEdge) || (leftEdge && downEdge))
			{
				ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNWSE);
			}
			else if ((rightEdge && downEdge) || (leftEdge && upEdge))
			{
				ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNESW);
			}
			else if (rightEdge || leftEdge)
			{
				ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
			}
			else if (upEdge || downEdge)
			{
				ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);
			}
		}
	}

	void SpriteEditor::Update()
	{
		{
			ImVec2 CursorPos = ImGui::GetCursorPos();
			myStartCursorPosition = { CursorPos.x, CursorPos.y - 32 };
		}

		ImVec2 windowSize = ImGui::GetWindowSize();
		myWindowSize = { windowSize.x, windowSize.y };

		if (ImGui::BeginMenuBar())
		{
			ImGui::SetCursorPosX(1);
			ImVec4 color{ backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w };

			if (ImGui::ColorButton("##ColorOfBackground", color))
			{
				ImGui::OpenPopup("##ColorPickerPopupOpen");
			}

			if (ImGui::BeginPopup("##ColorPickerPopupOpen"))
			{
				ImGui::ColorPicker3("##ColorPickerForSpriteEditBackground", &backgroundColor.x);

				ImGui::EndPopup();
			}

			ImGui::EndMenuBar();
		}

		MouseManager();

		if (ImGui::IsKeyPressed(ImGuiKey_Delete))
		{
			for (int i = 0; i < myRects.size(); i++)
			{
				if (myRects[i].isSelected)
				{
					myRects[i] = myRects.back();
					myRects.pop_back();
					i--;
				}
			}
		}

		if (!holdingRect)
		{
			if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
			{
				if (ImGui::IsKeyPressed(ImGuiKey_C))
				{
					myCopiedRectInfo = *mySelectedRectPtr;
				}
				if (ImGui::IsKeyPressed(ImGuiKey_V))
				{
					mySelectedRectPtr->isSelected = false;
					Rect rect = myCopiedRectInfo;
					myRects.emplace_back(rect);
					mySelectedRectPtr = &myRects.back();
					mySelectedRectPtr->isSelected = true;
				}
				if (ImGui::IsKeyPressed(ImGuiKey_D))
				{
					Rect rect = *mySelectedRectPtr;
					mySelectedRectPtr->isSelected = false;
					myRects.emplace_back(rect);
					mySelectedRectPtr = &myRects.back();
					mySelectedRectPtr->isSelected = true;
				}
			}
		}

		ImVec2 cursorScreenPos = ImGui::GetCursorScreenPos();
		if (holdingRect)
		{
			float posX = static_cast<float>(ImGui::GetMouseDragDelta().x) / myInspectorScale.x;
			float posY = static_cast<float>(ImGui::GetMouseDragDelta().y) / myInspectorScale.y;

			float positionSnappingX = roundf(posX / mySpriteScaleSnapping.x) * mySpriteScaleSnapping.x;
			float positionSnappingY = roundf(posY / mySpriteScaleSnapping.y) * mySpriteScaleSnapping.y;

			mySelectedRectPtr->position = { savedPositionBeforeMove.x + positionSnappingX, savedPositionBeforeMove.y + positionSnappingY };

			float clampedPositionX = std::clamp(mySelectedRectPtr->position.x, 0.f, static_cast<float>(myTextureSize.x) - mySelectedRectPtr->size.x);
			float clampedPositionY = std::clamp(mySelectedRectPtr->position.y, 0.f, static_cast<float>(myTextureSize.y) - mySelectedRectPtr->size.y);

			mySelectedRectPtr->position.x = clampedPositionX;
			mySelectedRectPtr->position.y = clampedPositionY;
		}
		else if (mouseIsDownLeft)
		{
			float posX = static_cast<float>(windowRelativeMousePosition.x) - myInspectorPositionOffsetFromZeroZero.x;
			float posY = static_cast<float>(windowRelativeMousePosition.y) - myInspectorPositionOffsetFromZeroZero.y;

			float snapScaleX = (mySpriteScaleSnapping.x * myInspectorScale.x);
			float snapScaleY = (mySpriteScaleSnapping.x * myInspectorScale.x);

			posX += snapScaleX * 0.5f;
			posY += snapScaleY * 0.5f;

			float positionSnappingX = roundf(posX / snapScaleX) * mySpriteScaleSnapping.x * myInspectorScale.x;
			float positionSnappingY = roundf(posY / snapScaleY) * mySpriteScaleSnapping.y * myInspectorScale.y;

			float spriteCurrentMaxX = std::clamp(static_cast<float>(positionSnappingX) + myInspectorPositionOffsetFromZeroZero.x, -myInspectorPosition.x, -myInspectorPosition.x + myTextureSize.x * myInspectorScale.x);
			float spriteCurrentMaxY = std::clamp(static_cast<float>(positionSnappingY) + myInspectorPositionOffsetFromZeroZero.y, myInspectorPosition.y, myInspectorPosition.y + myTextureSize.y * myInspectorScale.y);

			mySpriteCurrentMax = { spriteCurrentMaxX, spriteCurrentMaxY };

			ImGui::SetCursorPos(ImVec2(0, 0));

			ImVec2 minRect = ImVec2(mySpriteCurrentMin.x + cursorScreenPos.x, mySpriteCurrentMin.y + cursorScreenPos.y);
			ImVec2 maxRect = ImVec2(mySpriteCurrentMax.x + cursorScreenPos.x, mySpriteCurrentMax.y + cursorScreenPos.y);

			ImGui::GetForegroundDrawList()->AddRect(minRect, maxRect, (ImU32)IM_COL32(58, 128, 236, 255));
		}

		ImVec2 cursorPosScreen = ImGui::GetCursorScreenPos();
		cursorPosBeforeImage = { cursorPosScreen.x, cursorPosScreen.y };
		ImVec2 CursorPos = ImGui::GetCursorPos();

		CursorPos.x -= 8;
		CursorPos.y -= 8;

		ImVec2 imguiInspectorPos = ImVec2(-myInspectorPosition.x, myInspectorPosition.y);
		ImGui::SetCursorPos(imguiInspectorPos);

		imguiInspectorPos.x += cursorScreenPos.x;
		imguiInspectorPos.y += cursorScreenPos.y;

		ImVec2 spriteSize = ImVec2(myTextureSize.x * myInspectorScale.x, myTextureSize.y * myInspectorScale.y);

		ImU32 bgColor = IM_COL32(backgroundColor.x * 255.f, backgroundColor.y * 255.f, backgroundColor.z * 255.f, backgroundColor.w * 255.f);
		ImGui::GetWindowDrawList()->AddRectFilled(imguiInspectorPos, ImVec2(imguiInspectorPos.x + spriteSize.x, imguiInspectorPos.y + spriteSize.y), bgColor);

		ImGui::Image(myTexture->GetTextureID(), spriteSize, ImVec2(0, 0), ImVec2(1, 1));

		DrawRects();

		RectProperties();
	}

	void SpriteEditor::Open()
	{
		flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollWithMouse;

		myTexture = Resources::Get<Texture>("Assets/Sprites/ScissorSprite/Scissors.png");

		glBindTexture(GL_TEXTURE_2D, myTexture->GetTextureID());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, SamplingType::Point);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, SamplingType::Point);

		glBindTexture(GL_TEXTURE_2D, 0);


		myTextureSize = myTexture->GetTextureSize();
		mySpriteScaleSnapping = { static_cast<float>(myTextureSize.x), static_cast<float>(myTextureSize.y) };

		mySpriteScaleSnapping.x = 1.f;
		mySpriteScaleSnapping.y = 1.f;
	}
}
#endif