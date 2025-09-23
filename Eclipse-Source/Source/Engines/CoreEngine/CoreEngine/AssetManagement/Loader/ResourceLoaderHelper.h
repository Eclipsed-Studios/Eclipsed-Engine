#pragma once

namespace Eclipse
{
	class ResourceLoaderHelper final
	{
	public:
		static unsigned char* Load_Texture_STB(const char* aPath, class Texture& outResource);
		static unsigned char* Load_Texture_STB(const char* aPath, int& width, int& height, int& channels);

		static unsigned char* Resize_STB(unsigned char* original, int originalWidth, int originalHeight, int newWidth, int newHeight, int channels);

		static unsigned char* Load_Texture_From_Memory_STB(std::vector<unsigned char>& data, class Texture& outResource);

		static void FreeData_STB(unsigned char* someData);
	};
}