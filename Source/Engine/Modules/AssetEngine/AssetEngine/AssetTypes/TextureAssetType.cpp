#include "TextureAssetType.h"

#include "AssetEngine/Helper/STB_Helper.h"

#include "CoreEngine/EventSystem/EventSystem.h"

namespace Eclipse::Assets
{
	TextureAssetType::TextureAssetType()
	{
		defaultAssetsGuids[DefaultAssetType::TEXTURE_ERROR].FromString("cf50f44ea7fb40ed07c66d1190024581");
		defaultAssetsGuids[DefaultAssetType::TEXTURE_DEFAULT].FromString("77cbf21c126e6ab274908f75c436065b");
	}

	ImportedData TextureAssetType::Import(const AssetMeta& file)
	{
		EventSystem::Trigger("Texture_Imported", file);


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

		writer.Write(DATA_SIZE_PAIR(_data.width));
		writer.Write(DATA_SIZE_PAIR(_data.height));
		writer.Write(DATA_SIZE_PAIR(_data.channels));
		writer.Write(_data.Data.data(), _data.Data.size());
	}

	void TextureAssetType::Load(BinaryReader& reader, const AssetMeta& meta, AssetData* data)
	{
		TextureData* _data = reinterpret_cast<TextureData*>(data);

		reader.Read(DATA_SIZE_PAIR(_data->width));
		reader.Read(DATA_SIZE_PAIR(_data->height));
		reader.Read(DATA_SIZE_PAIR(_data->channels));

		std::vector<unsigned char> pixelData(_data->width * _data->height * _data->channels);
		reader.Read(pixelData.data(), pixelData.size());


		_data->dimDivOne.X = 1.f / static_cast<float>(_data->width);
		_data->dimDivOne.Y = 1.f / static_cast<float>(_data->height);
		_data->sizeNormalized = Math::Vector2f{ 1.f, static_cast<float>(_data->height) / _data->width };
		_data->guid = meta.guid;

		glGenTextures(1, &_data->textureID);
		glBindTexture(GL_TEXTURE_2D, _data->textureID);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x2901);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x2901);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 0x2601);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 0x2601);

		int rgbTypeOffset = GL_RGBA - _data->channels;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _data->width, _data->height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelData.data());
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}