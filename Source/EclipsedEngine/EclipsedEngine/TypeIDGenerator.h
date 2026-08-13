#pragma once

#include <unordered_map>

#include "EclipsedEngine.Core.hpp"

namespace Eclipse
{
	using TypeID = unsigned;

	class ECL_API TypeRegistry
	{
	public:
		template<typename T>
		static TypeID GetTypeID();
	};

	inline unsigned gTypeRegistryNextID = 1;
}



#include "TypeIDGenerator.inl"