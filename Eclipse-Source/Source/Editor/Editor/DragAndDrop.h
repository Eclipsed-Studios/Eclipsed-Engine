#pragma once

#include <vector>
#include <unordered_map>

#include "Math/Math.h"

#include "ImGui/ImGui/imgui.h"

namespace Eclipse::Editor
{
	class DragAndDrop
	{
	public:
		static inline bool BeginTarget(const char* text, const FileInfo::FileType_& type);

		static inline void BeginSource(const char* payload, const size_t& size, const FileInfo& info);

	private:
		static inline bool TextBox(const char* text, Math::Vector2f padding, const Math::Color& aBgColor, const Math::Color& aBorderColor, const char* id);


	public:
		static inline char payloadBuffer[256];
		static inline int index = 0;

		static inline std::unordered_map<FileInfo::FileType_, const char*> dnd_id =
		{
			{FileInfo::FileType_Audio, "DND_AUDIO"},
			{FileInfo::FileType_Texture, "DND_TEXTURE"},
			{FileInfo::FileType_Scene, "DND_SCENE"},
		};
	};
}