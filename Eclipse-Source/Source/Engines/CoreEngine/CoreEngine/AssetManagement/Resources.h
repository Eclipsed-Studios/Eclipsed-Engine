#pragma once

#include "ResourcePointer.h"
#include "AssetManagement/Loader/AssetLoader.hpp"
#include "ResourceList.h"

#include <typeindex>

#include <unordered_map>
#include <filesystem>
#include "Utilities/Files/FileInfo.h"

namespace Eclipse
{
	class Resources
	{
	public:
		static void Init();

		template<typename T>
		static ResourcePointer<T> Get(const char* aPath);

		template<typename T>
		static T* GetPointer(const size_t& aId);

		static void Update();

	private:
		static inline std::unordered_map<std::type_index, IResourceList*> myLoadedResources;
		static inline AssetLoader myLoader;
	};
}

#include "Resources.inl"