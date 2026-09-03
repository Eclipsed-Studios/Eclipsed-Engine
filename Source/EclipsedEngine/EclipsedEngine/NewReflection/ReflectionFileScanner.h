#pragma once

#include <string>

namespace Eclipse::Reflection
{
	class ReflectionFileScanner final 
	{
	public:
		static void ScanAndReflectFiles(const char* root);
		static void ReflectFile(const char* path);

	private:
		static std::string ReadFile(const char* path);
	};
}