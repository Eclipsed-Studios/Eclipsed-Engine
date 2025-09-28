#include <AssetManagement/Loader/AssetLoader.hpp>

#include <AssetManagement/Resources/Texture.h>
#include "AssetManagement/Loader/ResourceLoaderHelper.h"

#include <glad/glad.h>

#include <iomanip> 
#include <iterator>
#include <fstream>

namespace Eclipse
{
	template <>
	inline void AssetLoader::LoadFromPath(const char* aPath, Texture& outResource)
	{
		std::filesystem::path resolvedPath = aPath;
		if (resolvedPath.is_relative())
		{
			resolvedPath = std::filesystem::current_path().parent_path().generic_string() + "/" + resolvedPath.string();
		}
		else if (resolvedPath.is_absolute())
		{
			resolvedPath = aPath;
		}


		outResource = Texture(resolvedPath.string().c_str());

		std::ifstream in(SOURCE_PATH "Bin/assets.bundle", std::ios::binary);

		unsigned char* pixels = nullptr;
		size_t id = std::hash<std::string>{}(std::filesystem::path(aPath).generic_string());

#ifdef _GAME
		if (AssetLoader::loadedDatas.find(id) != AssetLoader::loadedDatas.end())
		{
			in.seekg(AssetLoader::loadedDatas[id].offset, std::ios::beg);

			std::vector<unsigned char> rawData;
			rawData.resize(AssetLoader::loadedDatas[id].size);

			in.read(reinterpret_cast<char*>(rawData.data()), AssetLoader::loadedDatas[id].size);
			in.close();

			pixels = ResourceLoaderHelper::Load_Texture_From_Memory_STB(rawData, outResource);
		}
#else
		pixels = ResourceLoaderHelper::Load_Texture_STB(resolvedPath.string().c_str(), outResource, true);
#endif

		glGenTextures(1, &outResource.textureID);
		glBindTexture(GL_TEXTURE_2D, outResource.textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapMode::Repeat);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapMode::Repeat);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, SamplingType::Bilinear);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, SamplingType::Bilinear);

		int rgbTypeOffset = 3 - outResource.channels;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB - rgbTypeOffset, outResource.width,
			outResource.height, 0, GL_RGB - rgbTypeOffset, GL_UNSIGNED_BYTE, pixels);
		glGenerateMipmap(GL_TEXTURE_2D);

		ResourceLoaderHelper::FreeData_STB(pixels);

		outResource.spriteDimDivOne = { 1.0f / static_cast<float>(outResource.width), 1.0f / static_cast<float>(outResource.height) };
		outResource.dimDivOne = 1.f / (static_cast<float>(outResource.height) / static_cast<float>(outResource.width));

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}