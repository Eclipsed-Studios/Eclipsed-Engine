#pragma once

#include <variant>

#include "AssetEngine/Assets/TextureAsset.h"
#include "AssetEngine/Assets/PrefabAsset.h"
#include "AssetEngine/Assets/MaterialAsset.h"
#include "AssetEngine/Assets/FontAsset.h"
#include "AssetEngine/Assets/AudioAsset.h"
#include "AssetEngine/Assets/Shader/VertexShaderAsset.h"
#include "AssetEngine/Assets/Shader/PixelShaderAsset.h"

namespace Eclipse::Assets
{
    using RuntimeAssetDataVariant = std::variant<
        AudioData*,
        FontData*,
        MaterialData*,
        TextureData*,
        PrefabData*,
        ShaderData*
    >;
};