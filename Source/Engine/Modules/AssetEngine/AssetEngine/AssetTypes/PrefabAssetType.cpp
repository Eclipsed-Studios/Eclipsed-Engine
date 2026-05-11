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
        return ProcessedData();
    }

    void PrefabAssetType::Serialize(BinaryWriter& writer, const ProcessedData& data)
    {
        if (!writer.IsOpen()) return;

        const ImportedPrefab& _data = std::get<ImportedPrefab>(data);

        const size_t size = _data.Data.size();
        writer.Write(DATA_SIZE_PAIR(size));
        writer.Write(_data.Data.data(), _data.Data.size());
    }

    void PrefabAssetType::Load(BinaryReader& reader, const AssetMeta& meta, AssetData* data)
    {
        
    }
}