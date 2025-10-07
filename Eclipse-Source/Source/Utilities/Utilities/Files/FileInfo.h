#pragma once

#include <filesystem>
#include "Font-Awesome/7/IconsFontAwesome7.h"
#include "Font-Awesome/7/IconsFontAwesome7Brands.h"

namespace Eclipse::Utilities
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

		FileStatus_ status;
		FileType_ type;
		std::filesystem::path filePath;
		std::filesystem::path relativeFilePath;

	public:
		const char* GetIcon() const;

		static FileInfo GetFileInfo(const std::filesystem::path& aPath);
		void SetRelativePath(const std::filesystem::path& rel);

	};
}