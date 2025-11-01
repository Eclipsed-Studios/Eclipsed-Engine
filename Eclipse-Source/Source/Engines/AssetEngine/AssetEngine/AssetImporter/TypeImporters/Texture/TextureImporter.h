#pragma once

#include "AssetEngine/AssetImporter/TypeImporters/Texture/STB_ImporterStrategy.h"
#include "AssetEngine/AssetImporter/TypeImporters/TypeImporter.h"
#include "AssetEngine/Models/AssetDatas/Binary/TextureBinaryData.h"
#include <string>
#include <unordered_map>


namespace Eclipse::Assets
{
	class TextureImporter : public TypeImporter<TextureBinaryData>
	{
	private:
		enum class Importer
		{
			STB
		};

		const std::unordered_map<std::string, Importer> typeToImporter =
		{
			{".png",  Importer::STB},
			{".jpg",  Importer::STB},
			{".jpeg", Importer::STB},
			{".bmp",  Importer::STB},
			{".tga",  Importer::STB},
			{".psd",  Importer::STB},
			{".gif",  Importer::STB},
			{".hdr",  Importer::STB},
			{".pic",  Importer::STB},
			{".pnm",  Importer::STB}
		};

	public:
		TextureImporter();

	public:
		void Import(TextureBinaryData& outData, const char* path, const char* relPath) override;

	private:
		std::unordered_map<Importer, AssetImporterStrategy<TextureBinaryData>*> importers;
	};
}