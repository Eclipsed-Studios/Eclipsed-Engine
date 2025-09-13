#pragma once

#include <unordered_map>

namespace Eclipse
{
	class IResourceList
	{
	public:
	};

	template<typename T>
	class ResourceList : public IResourceList
	{
	public:
		T* Get(const size_t& aId);
		T* Add(const size_t& aId);
		bool Exists(const size_t& aId);

	private:
		std::unordered_map<size_t, T> myIdToResource;
	};
}

#include "ResourceList.inl"