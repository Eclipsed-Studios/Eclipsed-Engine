#include "SceneAssetType.h"

#include "AssetEngine/Helper/STB_Helper.h"

#include "CoreEngine/EventSystem/EventSystem.h"

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
		data->guid = meta.guid;

	}
}