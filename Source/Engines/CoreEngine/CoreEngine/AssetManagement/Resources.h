#pragma once

#include "ResourcePointer.h"
#include "AssetManagement/Loader/AssetLoader.hpp"
#include "ResourceList.h"

#include <typeindex>

#include <unordered_map>

namespace Eclipse
{
	class Resources
	{
	public:
		template<typename T>
		static ResourcePointer<T> Get(const char* aPath);

		template<typename T>
		static T* GetPointer(const size_t& aId);



	private:
		static std::unordered_map<std::type_index, IResourceList*> myLoadedResources;
		static AssetLoader myLoader;
	};
}

#include "Resources.inl"