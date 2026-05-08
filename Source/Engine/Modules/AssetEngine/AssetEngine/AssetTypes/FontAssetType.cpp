#include "FontAssetType.h"

namespace Eclipse::Assets
{
    ImportedData FontAssetType::Import(const AssetMeta& file)
    {
        ImportedFont font;

        std::ifstream in(file.fullPath, std::ios::binary | std::ios::ate);
        size_t size = in.tellg();

        in.seekg(0);

        font.Data.resize(size);
        in.read(reinterpret_cast<char*>(font.Data.data()), size);

        return font;
    }

    ProcessedData FontAssetType::Process(const ImportedData& file)
    {
        return file;
    }

    void FontAssetType::Serialize(BinaryWriter& writer, const ProcessedData& data)
    {
        if (!writer.IsOpen()) return;

        const ImportedFont& _data = std::get<ImportedFont>(data);

        const size_t size = _data.Data.size();
        writer.Write(WRITE(size));
        writer.Write(_data.Data.data(), _data.Data.size());
    }

    RuntimeAsset FontAssetType::Load(BinaryReader& reader, const AssetMeta& meta)
    {
        return RuntimeAsset();
    }
}