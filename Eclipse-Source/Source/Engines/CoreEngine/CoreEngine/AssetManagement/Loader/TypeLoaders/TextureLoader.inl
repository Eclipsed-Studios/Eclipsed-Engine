#include <../CoreEngine/CoreEngine/AssetManagement/Loader/AssetLoader.hpp>

#include <../CoreEngine/CoreEngine/AssetManagement/Resources/Texture.h>
#include "../CoreEngine/CoreEngine/AssetManagement/Loader/ResourceLoaderHelper.h"

#include <iomanip> 
#include <iterator>
#include <fstream>

#include "rapidjson/rapidjson/document.h"
#include "rapidjson/rapidjson/filereadstream.h"

#include "../GraphicsEngine/GraphicsEngine/OpenGL/OpenGLGraphicsAPI.h"

namespace Eclipse
{
	inline void LoadSpriteRects(const rapidjson::Document& aDocument, std::vector<Math::RectSizePos>& myOutRects, Texture& outResource)
	{
		if (!aDocument.HasMember("Sprite Rects"))
			return;

		auto spriteRects = aDocument["Sprite Rects"].GetArray();

		float textureHeight = static_cast<float>(outResource.GetTextureSize().y);

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

			myOutRects.emplace_back(newRect);
		}
	}

	inline void LoadMetaFile(const char* aPath, Texture& outResource)
	{
		std::filesystem::path filePath = "../Assets";
		filePath /= outResource.GetRelativePath();
		filePath.replace_extension("meta");

		FILE* fileP = fopen(filePath.string().c_str(), "rb");
		if (!fileP)
			return;

		char readBuffer[32000];
		rapidjson::FileReadStream fileReadStream(fileP, readBuffer, sizeof(readBuffer));

		rapidjson::Document document;
		document.ParseStream(fileReadStream);
		fclose(fileP);

		LoadSpriteRects(document, outResource.myRects, outResource);
	}

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
		
		GraphicsEngine::CreateOpenGLTexture(outResource.textureID, outResource.spriteDimDivOne, outResource.dimDivOne, outResource.channels, outResource.width, outResource.height, pixels);
		
		ResourceLoaderHelper::FreeData_STB(pixels);
		LoadMetaFile(aPath, outResource);
	}
}