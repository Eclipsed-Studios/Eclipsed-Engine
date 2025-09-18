#pragma once

#include <filesystem>
#include "Font-Awesome/7/IconsFontAwesome7.h"
#include "Font-Awesome/7/IconsFontAwesome7Brands.h"

namespace Eclipse
{
	struct FileInfo
	{
		enum FileType_
		{
			FileType_None,
			FileType_Directory,

			FileType_Zip,
			FileType_Json,
			FileType_Font,
			FileType_Scene,
			FileType_Texture,
			FileType_Audio,
			FileType_Material,
			FileType_Shader,
			FileType_SpriteAnimation,
		};

		enum FileStatus_
		{
			FileStatus_NotFound,
			FileStatus_Ok,
			FileStatus_Directory,
			FileStatus_Symlink,
			FileStatus_Special,
			FileStatus_Unknown,
			FileStatus_NoPerm,
		};

		inline const char* GetIcon() const
		{
			static std::unordered_map<FileInfo::FileType_, const char*> fileTypeToIcon =
			{
				{FileInfo::FileType_Audio, ICON_FA_FILE_AUDIO},
				{FileInfo::FileType_Shader, ICON_FA_QUESTION},
				{FileInfo::FileType_Texture, ICON_FA_IMAGE},
				{FileInfo::FileType_Scene, ICON_FA_EARTH_EUROPE},
				{FileInfo::FileType_Font, ICON_FA_FONT},
				{FileInfo::FileType_SpriteAnimation, ICON_FA_PERSON_RUNNING},
				{FileInfo::FileType_Directory, ICON_FA_FOLDER},
				{FileInfo::FileType_Json, ICON_FA_FILE_EXCEL },
				{FileInfo::FileType_Zip, ICON_FA_FILE_ZIPPER},
			};

			const auto& it = fileTypeToIcon.find(type);
			if (it != fileTypeToIcon.end())
			{
				return it->second;
			}

			return ICON_FA_TRIANGLE_EXCLAMATION;
		}

		FileStatus_ status;
		FileType_ type;
		std::filesystem::path filePath;
	};
}