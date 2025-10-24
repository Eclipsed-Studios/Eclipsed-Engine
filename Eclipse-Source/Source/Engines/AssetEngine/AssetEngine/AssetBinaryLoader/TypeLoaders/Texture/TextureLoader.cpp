#include "TextureLoader.h"

#include <filesystem>
#include "AssetEngine/AssetImporter/TypeImporters/Texture/STB_ImporterStrategy.h"

#include "AssetEngine/AssetCooker/CookedAsset.h"
#include "AssetEngine/AssetRegistry.h"
#include "AssetEngine/PathManager.h"

namespace Eclipse::Assets
{
	TextureHandle* TextureLoader::Load(const size_t& id)
	{
		TextureHandle* handle = new TextureHandle;

		AssetRegistry& registry = AssetRegistry::GetInstance();
		if (!registry.IsRegistered(id)) return nullptr;

		std::filesystem::path path = PathManager::GetCookedAssetsDir() / (std::to_string(id) + ".asset");
		std::ifstream in(path, std::ios::binary);

		size_t d = 0;
		in.read(reinterpret_cast<char*>(&d), sizeof(size_t));
		in.read(reinterpret_cast<char*>(&handle->width), sizeof(int));
		in.read(reinterpret_cast<char*>(&handle->height), sizeof(int));
		in.read(reinterpret_cast<char*>(&handle->channels), sizeof(int));

		int pixelSize = handle->width * handle->channels * handle->height;
		char* pixels = new char[pixelSize];
		in.read(pixels, pixelSize);


		glGenTextures(1, &handle->textureID);
		glBindTexture(GL_TEXTURE_2D, handle->textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x2901);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x2901);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 0x2601);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 0x2601);

		int rgbTypeOffset = 3 - handle->channels;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB - rgbTypeOffset, handle->width, handle->height, 0, GL_RGB - rgbTypeOffset, GL_UNSIGNED_BYTE, pixels);
		glGenerateMipmap(GL_TEXTURE_2D);


		//spriteDivOne = { 1.0f / static_cast<float>(width), 1.0f / static_cast<float>(height) };
		//dimDivOne = 1.f / (static_cast<float>(height) / static_cast<float>(width));

		glBindTexture(GL_TEXTURE_2D, 0);


		delete[] pixels;
		return handle;
	}
}