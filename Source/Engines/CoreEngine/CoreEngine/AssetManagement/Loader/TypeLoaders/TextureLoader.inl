#include <AssetManagement/Loader/AssetLoader.hpp>

#include <AssetManagement/Resources/Texture.h>
#include "AssetManagement/Loader/ResourceLoaderHelper.h"

#include <glad/glad.h>


namespace ENGINE_NAMESPACE
{
	template <>
	inline void AssetLoader::LoadFromPath(const char* aPath, Texture& outResource)
	{
		outResource = Texture(aPath);

		unsigned char* data = ResourceLoaderHelper::Load_Texture_STB(aPath, outResource);

		glGenTextures(1, &outResource.textureID);
		glBindTexture(GL_TEXTURE_2D, outResource.textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapMode::Repeat);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapMode::Repeat);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, SamplingType::Bilinear);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, SamplingType::Bilinear);

		int rgbTypeOffset = 3 - outResource.channels;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB - rgbTypeOffset, outResource.width,
			outResource.height, 0, GL_RGB - rgbTypeOffset, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		ResourceLoaderHelper::FreeData_STB(data);

		outResource.spriteDimDivOne = {1.0f / static_cast<float>(outResource.width), 1.0f / static_cast<float>(outResource.height)};

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}