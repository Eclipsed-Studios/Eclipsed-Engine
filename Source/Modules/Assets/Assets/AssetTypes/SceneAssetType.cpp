#include "SceneAssetType.h"

#include "Core/Helpers/STB_Helper.h"

#include "Core/EventSystem/EventSystem.h"

namespace Eclipse::Assets
{
	ImportedData SceneAssetType::Import(const AssetMeta& file)
	{
		EventSystem::Trigger("Scene_Imported", file);

		ImportedScene data;

		std::ifstream in(file.fullPath);
		std::stringstream buffer;
		buffer << in.rdbuf();

		data.source = buffer.str();

		return data;
	}

	ProcessedData SceneAssetType::Process(const ImportedData& file)
	{
		return file;
	}

	void SceneAssetType::Serialize(BinaryWriter& writer, const ProcessedData& data)
	{
		if (!writer.IsOpen()) return;

		const ImportedScene& _data = std::get<ImportedScene>(data);

		const size_t size = _data.source.size();
		writer.Write(DATA_SIZE_PAIR(size));
		writer.Write(_data.source.data(), _data.source.size());
	}

	void SceneAssetType::Load(BinaryReader& reader, const AssetMeta& meta, AssetData* data)
	{
		SceneData* _data = reinterpret_cast<SceneData*>(data);

		_data->guid = meta.guid;

		size_t size = 0;
		reader.Read(reinterpret_cast<char*>(&size), sizeof(size_t));

		_data->sourceBlob.resize(size);
		reader.Read(_data->sourceBlob.data(), size);
	}

	void SceneAssetType::LoadFromBinary(BinaryReader& reader, const AssetMeta& meta, AssetData* data)
	{
		SceneData* _data = reinterpret_cast<SceneData*>(data);

		data->guid = meta.guid;
		reader.SetRead(meta.offset);

		size_t size = 0;
		reader.Read(reinterpret_cast<char*>(&size), sizeof(size_t));

		_data->sourceBlob.resize(meta.size);
		reader.Read(_data->sourceBlob.data(), meta.size - sizeof(size_t));
	}
}