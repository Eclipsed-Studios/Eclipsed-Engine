#include "MaterialAssetType.h"

#include "AssetEngine/BinaryFormats/MaterialData.h"

#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include "AssetEngine/AssetManager.h"

namespace Eclipse::Assets
{
    MaterialAssetType::MaterialAssetType()
    {
        defaultAssetsGuids[DefaultAssetType::MATERIAL_2D_SPRITE].FromString("304024b18cd756152dee092f1a43738d");
    }

    ImportedData MaterialAssetType::Import(const AssetMeta& file)
    {
        ImportedMaterial material;

        SerializableMaterialData matData;        
        std::ifstream in(file.fullPath, std::ios::binary);

        cereal::JSONInputArchive ar(in);
        ar(matData);

        material.pixelShaderID.FromString(matData.pixelShaderGuidStr);
        material.vertexShaderID.FromString(matData.vertexShaderGuidStr);
        material.textureID.FromString(matData.textureGuidStr);
        material.color = matData.color;

        return material;
    }

    ProcessedData MaterialAssetType::Process(const ImportedData& file)
    {
        return ProcessedData();
    }

    void MaterialAssetType::Serialize(BinaryWriter& writer, const ProcessedData& data)
    {
        if (!writer.IsOpen()) return;

        const ImportedMaterial& _data = std::get<ImportedMaterial>(data);

        writer.Write(DATA_SIZE_PAIR(_data.color));
        writer.Write(DATA_SIZE_PAIR(_data.pixelShaderID));
        writer.Write(DATA_SIZE_PAIR(_data.vertexShaderID));
        writer.Write(DATA_SIZE_PAIR(_data.textureID));
    }

    void MaterialAssetType::Load(BinaryReader& reader, const AssetMeta& meta, AssetData* data)
    {
        MaterialData* _data = reinterpret_cast<MaterialData*>(data);

        reader.Read(DATA_SIZE_PAIR(_data->color));


        GUID pixelShaderID, vertexShaderID, textureID;
        reader.Read(DATA_SIZE_PAIR(pixelShaderID));
        reader.Read(DATA_SIZE_PAIR(vertexShaderID));
        reader.Read(DATA_SIZE_PAIR(textureID));

        _data->pixelShader = AssetManager::Load<PixelShader>(pixelShaderID);
        _data->vertexShader = AssetManager::Load<VertexShader>(vertexShaderID);
        _data->texture = AssetManager::Load<Texture>(textureID);
        _data->guid = meta.guid;

        if (!_data->pixelShader.IsValid())
        {
            // Fallback to error shader
        }

        if (!_data->vertexShader.IsValid())
        {
            // Fallback to error shader
        }

        _data->programID = glCreateProgram();
        glAttachShader(_data->programID, _data->vertexShader.GetProgramID());
        glAttachShader(_data->programID, _data->pixelShader.GetProgramID());
        glLinkProgram(_data->programID);
    }

    void MaterialAssetType::LoadFromBinary(BinaryReader& reader, const AssetMeta& meta, AssetData* data)
    {
        MaterialData* _data = reinterpret_cast<MaterialData*>(data);

        data->guid = meta.guid;
        reader.SetRead(meta.offset);

        reader.Read(DATA_SIZE_PAIR(_data->color));


        GUID pixelShaderID, vertexShaderID, textureID;
        reader.Read(DATA_SIZE_PAIR(pixelShaderID));
        reader.Read(DATA_SIZE_PAIR(vertexShaderID));
        reader.Read(DATA_SIZE_PAIR(textureID));

        _data->pixelShader = AssetManager::Load<PixelShader>(pixelShaderID);
        _data->vertexShader = AssetManager::Load<VertexShader>(vertexShaderID);
        _data->texture = AssetManager::Load<Texture>(textureID);
        _data->guid = meta.guid;


        if (!_data->pixelShader.IsValid())
        {
            // Fallback to error shader
        }

        if (!_data->vertexShader.IsValid())
        {
            // Fallback to error shader
        }

        _data->programID = glCreateProgram();
        glAttachShader(_data->programID, _data->vertexShader.GetProgramID());
        glAttachShader(_data->programID, _data->pixelShader.GetProgramID());
        glLinkProgram(_data->programID);
    }
}