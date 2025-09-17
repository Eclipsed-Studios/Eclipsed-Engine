#pragma once

#include "ResourcePointer.h"
#include "AssetManagement/Loader/AssetLoader.hpp"
#include "ResourceList.h"

#include <typeindex>

#include <unordered_map>

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

		const char* GetIcon() const;

		FileStatus_ status;
		FileType_ type;
		std::filesystem::path filePath;
	};

	class Resources
	{
	public:
		template<typename T>
		static ResourcePointer<T> Get(const char* aPath);

		template<typename T>
		static T* GetPointer(const size_t& aId);

		static FileInfo GetFileInfo(const std::filesystem::path& aPath);
		static std::string ResolveFilePath(const std::string& aPath);

	private:
		static inline std::unordered_map<std::type_index, IResourceList*> myLoadedResources;
		static inline AssetLoader myLoader;
	};
}

#include "Resources.inl"