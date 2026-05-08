#include "TextureAssetType.h"

#include "AssetEngine/Helper/STB_Helper.h"

namespace Eclipse::Assets
{
    ImportedData TextureAssetType::Import(const AssetMeta& file)
    {
		ImportedTexture data;

		unsigned char* pixelData;
		pixelData = STB_Helper::Load_Texture_STB(file.fullPath.generic_string().c_str(), data.width, data.height, data.channels, true);

        const size_t size = data.width * data.height * data.channels;
        data.Data.resize(size);
        memcpy(data.Data.data(), pixelData, size);
		STB_Helper::FreeData_STB(pixelData);

		//TextureAssetMetaSettings texMetaSettings = LoadOrCreateMeta<TextureAssetMetaSettings>(aPath);
		//int dataAmount = texMetaSettings.spriteRects.size();
		//outStream.write(reinterpret_cast<const char*>(&dataAmount), sizeof(int));
		//outStream.write(reinterpret_cast<const char*>(texMetaSettings.spriteRects.data()), dataAmount);

        return data;
    }

    ProcessedData TextureAssetType::Process(const ImportedData& file)
    {
        return file;

    }

    void TextureAssetType::Serialize(BinaryWriter& writer, const ProcessedData& data)
    {
        if (!writer.IsOpen()) return;

        const ImportedTexture& _data = std::get<ImportedTexture>(data);

        writer.Write(WRITE(_data.width));
        writer.Write(WRITE(_data.height));
        writer.Write(WRITE(_data.channels));
        writer.Write(_data.Data.data(), _data.Data.size());
    }

    RuntimeAsset TextureAssetType::Load(BinaryReader& reader, const AssetMeta& meta)
    {
        return RuntimeAsset();
    }
}