#pragma once

namespace ENGINE_NAMESPACE
{
	class Resources;
	template<typename ResourceType>
	class ResourcePointer
	{
	public:
		ResourcePointer() = default;
		ResourcePointer(const size_t& resourceID);

		ResourceType* Get();
		const ResourceType* Get() const;

		ResourceType* operator->();
		const ResourceType* operator->() const;

		inline ResourcePointer& operator=(const ResourcePointer& other)
		{
			if (this != &other) 
			{
				id = other.id;  
			}
			return *this;
		}


	private:
		size_t id;
	};
}

#include "ResourcePointer.inl"