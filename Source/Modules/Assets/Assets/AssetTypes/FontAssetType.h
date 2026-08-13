#pragma once

#include "IAssetType.h"

namespace Eclipse::Assets
{
    class FontAssetType : public IAssetType
    {
    public:
        FontAssetType();

        ImportedData Import(const AssetMeta& file) override;
        ProcessedData Process(const ImportedData& file) override;
        void Serialize(BinaryWriter& writer, const ProcessedData& data) override;
        void Load(BinaryReader& reader, const AssetMeta& meta, AssetData* data) override;
        void LoadFromBinary(BinaryReader& reader, const AssetMeta& meta, AssetData* data) override;
    };
}