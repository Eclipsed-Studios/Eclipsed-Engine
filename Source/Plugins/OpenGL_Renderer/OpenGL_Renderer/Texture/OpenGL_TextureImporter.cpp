#include "OpenGL_TextureImporter.h"

using namespace Eclipse::Assets;

namespace Eclipse::Graphics::OpenGL::Assets
{
    ImportedData OpenGL_TextureImporter::Import(const AssetMeta& meta)
    {
        return {};
    }
    
    ImportedData OpenGL_TextureImporter::Import(const char* path)
    {
        return {};
    }

    AssetData* OpenGL_TextureImporter::Process(const ImportedData& importedData)
    {
        return nullptr;
    }

    void OpenGL_TextureImporter::Serialize(const AssetData& data)
    {

    }

    AssetData* OpenGL_TextureImporter::Deserialize(const AssetMeta& assetMeta)
    {
        return nullptr;
    }

    AssetData* OpenGL_TextureImporter::Deserialize(const char* path)
    {
        return nullptr;
    }
}