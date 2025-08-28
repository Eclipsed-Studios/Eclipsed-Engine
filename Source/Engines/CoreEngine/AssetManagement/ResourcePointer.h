#pragma once

namespace ENGINE_NAMESPACE
{
	template<typename ResourceType>
	class ResourcePointer
	{
	public:
		ResourcePointer(const size_t& resourceID);

		ResourceType* Get();
		const ResourceType* Get() const;

	private:
		const size_t id;
	};
}

#include "ResourcePointer.h"