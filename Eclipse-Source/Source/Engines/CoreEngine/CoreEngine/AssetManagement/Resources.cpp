#include "Resources.h"


namespace Eclipse
{
	FileInfo Resources::GetFileInfo(const std::filesystem::path& aPath)
	{
		static std::unordered_map<std::string, FileInfo::FileType_> files =
		{
			{".png", FileInfo::FileType_Texture}, 
			{".jpg", FileInfo::FileType_Texture}, 
			{".jpeg", FileInfo::FileType_Texture}, 
			{".bmp", FileInfo::FileType_Texture}, 
			{".tga", FileInfo::FileType_Texture}, 
			{".gif", FileInfo::FileType_Texture}, 
			{".psd", FileInfo::FileType_Texture}, 
			{".hdr", FileInfo::FileType_Texture}, 

			{".glsl", FileInfo::FileType_Shader}, 

			{".scene", FileInfo::FileType_Scene},

			{".wav", FileInfo::FileType_Audio},
			{".mp3", FileInfo::FileType_Audio},

			{".zip", FileInfo::FileType_Zip},

			{".json", FileInfo::FileType_Json},

			{".ttf", FileInfo::FileType_Font},
			{".TTF", FileInfo::FileType_Font},

			{".spriteanim", FileInfo::FileType_SpriteAnimation}, 

			{".spriteanim", FileInfo::FileType_SpriteAnimation}, 
		};

		FileInfo info;
		info.filePath = aPath;

		std::filesystem::file_status status = std::filesystem::status(aPath);
		switch (status.type())
		{
		case std::filesystem::file_type::not_found: info.status = FileInfo::FileStatus_NotFound; break;
		case std::filesystem::file_type::regular:   
		{
			info.status = FileInfo::FileStatus_Ok;
			info.type = files[aPath.filename().extension().string()];
		}break;
		case std::filesystem::file_type::directory: 
		{
			info.status = FileInfo::FileStatus_Directory;
			info.type = FileInfo::FileType_Directory;
		}break;
		case std::filesystem::file_type::symlink:   info.status = FileInfo::FileStatus_Symlink; break;

		case std::filesystem::file_type::block:
		case std::filesystem::file_type::character:
		case std::filesystem::file_type::fifo:
		case std::filesystem::file_type::socket:
			info.status = FileInfo::FileStatus_Special; break;

		default: info.status = FileInfo::FileStatus_Unknown; break;
		}

		return info;
	}
}