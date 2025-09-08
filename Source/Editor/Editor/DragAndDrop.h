#pragma once

#include <vector>
#include <unordered_map>

#include "Math/Color.h"

namespace ENGINE_NAMESPACE::Editor
{
	class DragAndDrop
	{
	public:
		static inline bool TextBox(const char* text, Math::Vector2f padding, const Math::Color& aBgColor, const Math::Color& aBorderColor, const char* id)
		{
			ImGui::PushID(id);

			float availableWidth = ImGui::GetContentRegionAvail().x;
			float maxWidth = availableWidth > 50.0f ? availableWidth : 50.0f;
			ImGui::PushTextWrapPos(ImGui::GetCursorPosX() + maxWidth - padding.x);
			ImVec2 textSize = ImGui::CalcTextSize(text, nullptr, false, maxWidth - padding.x * 2.0f);
			ImVec2 boxSize = ImVec2(maxWidth, textSize.y + padding.y * 2.0f);
			ImVec2 pos = ImGui::GetCursorScreenPos();
			ImGui::GetWindowDrawList()->AddRectFilled(
				pos, ImVec2(pos.x + boxSize.x, pos.y + boxSize.y), ImGui::GetColorU32({ aBgColor.r, aBgColor.g, aBgColor.b, 1.f }));
			ImGui::GetWindowDrawList()->AddRect(
				pos, ImVec2(pos.x + boxSize.x, pos.y + boxSize.y), ImGui::GetColorU32({ aBorderColor.r, aBorderColor.g, aBorderColor.b, 1.f }),
				0.0f, ImDrawFlags_RoundCornersNone, 1.5f);

			ImGui::SetCursorScreenPos(ImVec2(pos.x + padding.x, pos.y + padding.y));
			ImGui::TextWrapped("%s", text);

			ImGui::SetCursorScreenPos(ImVec2(pos.x, pos.y + boxSize.y));

			ImGui::PopTextWrapPos();
			ImGui::PopID();

			return false;
		}

	public:
		enum class AssetDragAndDropIdx
		{
			Texture,
			Audio,
		};

		static inline std::vector<const char*> dragAndDropString = {
			"DND_TEXTURE",
			"DND_AUDIO",
		};

		static inline std::unordered_map<std::string, AssetDragAndDropIdx> supportedFileTypes =
		{
			{".png", AssetDragAndDropIdx::Texture},
			{".jpg", AssetDragAndDropIdx::Texture},
			{".jpeg", AssetDragAndDropIdx::Texture},
			{".bmp", AssetDragAndDropIdx::Texture},
			{".tga", AssetDragAndDropIdx::Texture},
			{".gif", AssetDragAndDropIdx::Texture},
			{".psd", AssetDragAndDropIdx::Texture},
			{".hdr", AssetDragAndDropIdx::Texture},
			{".mp3", AssetDragAndDropIdx::Audio},
			{".wav", AssetDragAndDropIdx::Audio},
		};
	};
}