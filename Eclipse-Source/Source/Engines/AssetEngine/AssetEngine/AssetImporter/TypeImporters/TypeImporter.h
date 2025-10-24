#pragma once

namespace Eclipse
{
	template<typename T>
	class TypeImporter
	{
	public:
		virtual void Import(T& outData, const char* path) = 0;
	};
}