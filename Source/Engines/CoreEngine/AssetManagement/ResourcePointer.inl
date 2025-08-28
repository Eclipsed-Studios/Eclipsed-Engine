#include "ResourcePointer.h"

namespace ENGINE_NAMESPACE
{
	template<typename ResourceType>
	inline ResourcePointer<ResourceType>::ResourcePointer(const size_t& resourceID)
		: id(resourceID) {}
}