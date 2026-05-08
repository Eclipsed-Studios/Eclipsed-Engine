#include "MaterialAssetType.h"

#include "AssetEngine/BinaryFormats/MaterialData.h"

#include "cereal/cereal.hpp"

namespace Eclipse::Assets
{
    ImportedData MaterialAssetType::Import(const AssetMeta& file)
    {
        //ImportedMaterial material;

        //MaterialData matData;
        //std::ifstream in(file.fullPath, std::ios::binary);

        //cereal::JSONInputArchive ar(in);
        //ar(matData);

        return ImportedData();
    }

    ProcessedData MaterialAssetType::Process(const ImportedData& file)
    {
        return ProcessedData();

    }

    void MaterialAssetType::Serialize(BinaryWriter& writer, const ProcessedData& data)
    {

    }

    RuntimeAsset MaterialAssetType::Load(BinaryReader& reader, const AssetMeta& meta)
    {
        return RuntimeAsset();
    }
}