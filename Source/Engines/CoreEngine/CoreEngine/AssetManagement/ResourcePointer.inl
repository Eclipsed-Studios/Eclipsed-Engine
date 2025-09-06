#include "ResourcePointer.h"

#include "Resources.h"

namespace ENGINE_NAMESPACE
{
	template<typename ResourceType>
	inline ResourcePointer<ResourceType>::ResourcePointer(const size_t& resourceID)
		: id(resourceID) {}


	template<typename ResourceType>
	inline ResourceType* ResourcePointer<ResourceType>::Get()
	{
		return Resources::template GetPointer<ResourceType>(id);;
	}

	template<typename ResourceType>
	inline const ResourceType* ResourcePointer<ResourceType>::Get() const
	{
		return Resources::template GetPointer<ResourceType>(id);;
	}

	template<typename ResourceType>
	inline ResourceType* ResourcePointer<ResourceType>::operator->()
	{
		return Resources::template GetPointer<ResourceType>(id);
	}

	template<typename ResourceType>
	inline const ResourceType* ResourcePointer<ResourceType>::operator->() const
	{
		return Resources::template GetPointer<ResourceType>(id);
	}
}