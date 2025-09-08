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
		~ResourcePointer();

		ResourcePointer(ResourcePointer&& other) noexcept; 
		ResourcePointer& operator=(ResourcePointer&& other) noexcept
		{
			id = other.id;
			other.id = 0;

			return *this;
		}

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

		operator bool() const noexcept
		{
			return Get() != nullptr;
		}


	private:
		size_t id;
	};
}

#include "ResourcePointer.inl"