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

		handle->assetID = id;

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

		glBindTexture(GL_TEXTURE_2D, 0);

		LoadMetaFile(id, handle);
		
		handle->dimDivOne = 1.f / (static_cast<float>(handle->height) / static_cast<float>(handle->width));
		handle->sizeNormalized = Math::Vector2f{ 1.f, static_cast<float>(handle->height) / handle->width };


		delete[] pixels;
		return handle;
	}
	















	void TextureLoader::LoadMetaFile(const size_t& id, TextureHandle* handle)
	{
		AssetRegistry& registry = AssetRegistry::GetInstance();
		auto& entry = registry.GetRegisteredAsset(id);

		std::filesystem::path filePath = entry.path;
		filePath.replace_extension(".meta");
		
		FILE* fileP = fopen(filePath.string().c_str(), "rb");
		if (!fileP)
			return;

		char readBuffer[32000];
		rapidjson::FileReadStream fileReadStream(fileP, readBuffer, sizeof(readBuffer));

		rapidjson::Document document;
		document.ParseStream(fileReadStream);
		fclose(fileP);



		if (!document.HasMember("Sprite Rects"))
			return;

		auto spriteRects = document["Sprite Rects"].GetArray();

		float textureHeight = static_cast<float>(handle->height);

		for (auto& rect : spriteRects)
		{
			Math::RectSizePos newRect;

			const rapidjson::Value& position = rect["pos"];
			const rapidjson::Value& size = rect["size"];

			if (size.HasMember("width") && size["width"].IsNumber())
				newRect.size.x = size["width"].GetFloat();

			if (size.HasMember("height") && size["height"].IsNumber())
				newRect.size.y = size["height"].GetFloat();

			if (position.HasMember("x") && position["x"].IsNumber())
				newRect.position.x = position["x"].GetFloat();

			if (position.HasMember("y") && position["y"].IsNumber())
				newRect.position.y = std::fmod((textureHeight - position["y"].GetFloat() + newRect.size.y), textureHeight);

			handle->rects.emplace_back(newRect);
		}
	}
}