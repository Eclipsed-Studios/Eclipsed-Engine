#include "SpriteAnimationLoader.h"

#include "AssetEngine/AssetRegistry.h"
#include "CoreEngine/PathManager.h"

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <fstream>

namespace Eclipse::Assets
{
    SpriteAnimationHandle* SpriteAnimationLoader::Load(const size_t& id)
    {
        SpriteAnimationHandle* handle = new SpriteAnimationHandle;
        Load(id, handle);

        return handle;
    }

    void SpriteAnimationLoader::Load(const size_t& id, SpriteAnimationHandle* handle)
    {
        handle->assetID = id;

        AssetRegistry& registry = AssetRegistry::GetInstance();
        if (!registry.IsRegistered(id)) return;

        std::filesystem::path path = PathManager::GetCookedAssetsDir() / (std::to_string(id) + ".asset");
        std::ifstream in(path, std::ios::binary);

        
    }
}