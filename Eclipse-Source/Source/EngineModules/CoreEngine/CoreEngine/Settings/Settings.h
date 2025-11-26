#pragma once

#include <string>

namespace Eclipse
{
	class Settings
	{
	public:
		template<typename T>
		T Get(const char* key);

		template<typename T>
		void Set(const char* key, T& value);
	};
}

#include "Settings.inl"