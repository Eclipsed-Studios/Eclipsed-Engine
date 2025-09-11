#include "Resources.h"

#include <filesystem>

namespace Eclipse
{
	template<typename T>
	inline ResourcePointer<T> Resources::Get(const char* aPath)
	{
		std::type_index idx = std::type_index(typeid(T));
		if (myLoadedResources.find(idx) == myLoadedResources.end())
		{
			myLoadedResources[idx] = new ResourceList<T>();
		}

		ResourceList<T>* list = (ResourceList<T>*)myLoadedResources[idx];

		T* resource = nullptr;
		size_t id = std::hash<std::string>{}(aPath);
		if (list->Exists(id))
		{
			resource = list->Get(id);
		}
		else
		{
			resource = list->Add(id);
			myLoader.LoadFromPath(aPath, *resource);
		}

		ResourcePointer<T> ptr(id);
		return ptr;
	}


	template<typename T>
	inline T* Resources::GetPointer(const size_t& aId)
	{
		std::type_index idx = std::type_index(typeid(T));
		if (myLoadedResources.find(idx) == myLoadedResources.end())
		{
			myLoadedResources[idx] = new ResourceList<T>();
		}

		ResourceList<T>* list = (ResourceList<T>*)myLoadedResources[idx];

		T* resource = nullptr;
		if (list->Exists(aId))
		{
			resource = list->Get(aId);
		}

		return resource;
	}
}