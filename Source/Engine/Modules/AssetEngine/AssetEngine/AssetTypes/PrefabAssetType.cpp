#include "PrefabAssetType.h"

namespace Eclipse::Assets
{
    ImportedData PrefabAssetType::Import(const AssetMeta& file)
    {
        ImportedPrefab prefab;

        std::ifstream in(file.fullPath, std::ios::binary | std::ios::ate);
        size_t size = in.tellg();

        in.seekg(0);

        prefab.Data.resize(size);
        in.read(reinterpret_cast<char*>(prefab.Data.data()), size);

        return prefab;
    }

    ProcessedData PrefabAssetType::Process(const ImportedData& file)
    {
        return file;
    }

    void PrefabAssetType::Serialize(BinaryWriter& writer, const ProcessedData& data)
    {
        if (!writer.IsOpen()) return;

        const ImportedPrefab& _data = std::get<ImportedPrefab>(data);

        const size_t strSize = _data.Data.size();
        writer.Write(DATA_SIZE_PAIR(strSize));
        writer.Write(_data.Data.data(), _data.Data.size());
    }

    void PrefabAssetType::Load(BinaryReader& reader, const AssetMeta& meta, AssetData* data)
    {
        PrefabData* _data = reinterpret_cast<PrefabData*>(data);


        size_t strSize = 0;
        reader.Read(DATA_SIZE_PAIR(strSize));

        _data->data = reinterpret_cast<char*>(malloc(strSize));
        reader.Read(_data->data, strSize);
        memset(_data->data + strSize, 0, 1);

        _data->guid = meta.guid;
    }

    void PrefabAssetType::LoadFromBinary(BinaryReader& reader, const AssetMeta& meta, AssetData* data)
    {
        PrefabData* _data = reinterpret_cast<PrefabData*>(data);

        reader.SetRead(meta.offset);

        size_t strSize = 0;
        reader.Read(DATA_SIZE_PAIR(strSize));

        _data->data = reinterpret_cast<char*>(malloc(strSize));
        reader.Read(_data->data, strSize);
        memset(_data->data + strSize, 0, 1);

        _data->guid = meta.guid;
    }
}