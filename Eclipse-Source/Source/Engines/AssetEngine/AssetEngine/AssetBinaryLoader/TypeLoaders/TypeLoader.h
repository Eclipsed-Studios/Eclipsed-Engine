#pragma once

namespace Eclipse
{
	template<typename T>
	class TypeLoader
	{
	public:
		virtual T* Load(const size_t& id) = 0;
	};
}