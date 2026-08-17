#pragma once

#include "EclipsedEngine/AssetManager/AssetData/AssetData.h"
#include "EclipsedEngine/AssetManager/ImportedData.h"
#include "EclipsedEngine/AssetManager/MetaData/AssetMeta.h"

#include "EclipsedEngine/AssetManager/AssetTypes.h"

namespace Eclipse::Assets
{
    struct IAssetImporter
    {
    public:
        virtual ImportedData Import(const AssetMeta& meta) = 0;
        virtual ImportedData Import(const char* path) = 0;

        virtual AssetData* Process(const ImportedData& importedData) = 0;

        virtual void Serialize(const AssetData& data) = 0;

        virtual AssetData* Deserialize(const AssetMeta& assetMeta) = 0;
        virtual AssetData* Deserialize(const char* path) = 0;

        AssetType typeToLoad = AssetType::Unknown;
    };
}