#pragma once

#include "AssetEngine/Core/ImportedData.h"
#include "AssetEngine/Core/RuntimeAsset.h"
#include "AssetEngine/Metadata/AssetMeta.h"

#include "AssetEngine/IO/BinaryWriter.h"
#include "AssetEngine/IO/BinaryReader.h"


#define REQUIRES_PROCESSING public: bool NeedsProcessing() const override {return true;}

namespace Eclipse::Assets
{
    enum class DefaultAssetType
    {
        VERTEX_SHADER_UI,
        VERTEX_SHADER_SPRITE,

        TEXTURE_DEFAULT,
        TEXTURE_ERROR,

        MATERIAL_2D_SPRITE
    };

    class BinaryReader;

    class IAssetType
    {
    public:
        virtual ImportedData Import(const AssetMeta& file) = 0;
        virtual ProcessedData Process(const ImportedData& file) = 0;
        virtual void Serialize(BinaryWriter& writer, const ProcessedData& data) = 0;
        virtual void Load(BinaryReader& reader, const AssetMeta& meta, AssetData* data) = 0;

        virtual bool NeedsProcessing() const { return false;}

    public:
        GUID GetDefaultAsset(DefaultAssetType defaultAsset) const;

    protected:
        std::unordered_map<DefaultAssetType, GUID> defaultAssetsGuids;
    };
}