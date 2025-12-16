#pragma once

#include <unordered_map>

//#include "CoreEngine/Macros/defines.h"

namespace Eclipse
{
	using TypeID = unsigned;

	class TypeRegistry
	{
	public:
		template<typename T>
		static TypeID GetTypeID();

	private:
		inline static unsigned nextId = 0;
	};
}

#include "TypeIDGenerator.inl"