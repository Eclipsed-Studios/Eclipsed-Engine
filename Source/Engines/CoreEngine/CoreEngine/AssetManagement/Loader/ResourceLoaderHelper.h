#pragma once

namespace ENGINE_NAMESPACE
{
	class ResourceLoaderHelper final
	{
	public:
		static unsigned char* Load_Texture_STB(const char* aPath, class Texture& outResource);
		static void FreeData_STB(unsigned char* someData);
	};
}