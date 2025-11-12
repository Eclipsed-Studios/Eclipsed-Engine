#pragma once

#include <unordered_map>

namespace Eclipse
{
	class IResourceList
	{
	public:
		virtual void Remove(const size_t& aId) = 0;
	};

	template<typename T>
	class ResourceList : public IResourceList
	{
	public:
		T* Get(const size_t& aId);

		T* Add(const size_t& aId);
		void Remove(const size_t& aId) override;

		bool Exists(const size_t& aId);

	private:
		std::unordered_map<size_t, T> myIdToResource;
	};
}

#include "ResourceList.inl"