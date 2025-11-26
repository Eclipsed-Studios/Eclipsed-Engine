#include "Settings.h"

namespace Eclipse
{
	template<typename T>
	inline T Eclipse::Settings::Get(const char* key)
	{
		return T();
	}

	template<typename T>
	inline void Settings::Set(const char* key, T& value)
	{
	}
}