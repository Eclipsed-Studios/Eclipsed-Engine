#include "PixelShaderAssetType.h"

#include "Helper/ShaderCompiler.h"
#include "OpenGL/glad/glad.h"

namespace Eclipse::Assets
{
    PixelShaderAssetType::PixelShaderAssetType()
    {
    }
    ImportedData PixelShaderAssetType::Import(const AssetMeta& file)
    {
        ImportedShader shader;

        std::ifstream in(file.fullPath, std::ios::binary | std::ios::ate);
        size_t size = in.tellg();

        in.seekg(0);

        shader.source.resize(size);
        in.read(reinterpret_cast<char*>(shader.source.data()), size);

        return shader;
    }

    ProcessedData PixelShaderAssetType::Process(const ImportedData& file)
    {
        return ProcessedData();

    }

    void PixelShaderAssetType::Serialize(BinaryWriter& writer, const ProcessedData& data)
    {
        if (!writer.IsOpen()) return;

        const ImportedShader& _data = std::get<ImportedShader>(data);

        const size_t size = _data.source.size();
        writer.Write(DATA_SIZE_PAIR(size));
        writer.Write(_data.source.data(), size);
    }

    void PixelShaderAssetType::Load(BinaryReader& reader, const AssetMeta& meta, AssetData* data)
    {
        ShaderData* _data = reinterpret_cast<ShaderData*>(data);

        size_t size;
        reader.Read(DATA_SIZE_PAIR(size));

        std::string shaderSource;
        shaderSource.resize(size);

        reader.Read(shaderSource.data(), size);

        ShaderCompileInfo info = ShaderCompiler::CompileShaderFromMemory(GL_FRAGMENT_SHADER, shaderSource.data());
        _data->shaderProgramID = info.shaderID;
        _data->guid = meta.guid;
    }

    void PixelShaderAssetType::LoadFromBinary(BinaryReader& reader, const AssetMeta& meta, AssetData* data)
    {
        ShaderData* _data = reinterpret_cast<ShaderData*>(data);

        data->guid = meta.guid;
        reader.SetRead(meta.offset);

        size_t size;
        reader.Read(DATA_SIZE_PAIR(size));

        std::string shaderSource;
        shaderSource.resize(size);

        reader.Read(shaderSource.data(), size);

        ShaderCompileInfo info = ShaderCompiler::CompileShaderFromMemory(GL_FRAGMENT_SHADER, shaderSource.data());
        _data->shaderProgramID = info.shaderID;
        _data->guid = meta.guid;
    }
}