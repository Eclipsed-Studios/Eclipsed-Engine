#include "ResourceList.h"

namespace Eclipse
{
	template<typename T>
	inline T* ResourceList<T>::Get(const size_t& aId)
	{
		return &myIdToResource[aId];
	}

	template<typename T>
	inline T* ResourceList<T>::Add(const size_t& aId)
	{
		myIdToResource.emplace(aId, T());
		return &myIdToResource[aId];
	}

	template<typename T>
	inline void ResourceList<T>::Remove(const size_t& aId)
	{
	}

	template<typename T>
	inline bool ResourceList<T>::Exists(const size_t& aId)
	{
		return myIdToResource.find(aId) != myIdToResource.end();
	}
}