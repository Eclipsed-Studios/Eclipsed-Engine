#pragma once

#include <variant>

#include "Assets/Assets/TextureAsset.h"
#include "Assets/Assets/PrefabAsset.h"
#include "Assets/Assets/MaterialAsset.h"
#include "Assets/Assets/FontAsset.h"
#include "Assets/Assets/AudioAsset.h"
#include "Assets/Assets/Shader/VertexShaderAsset.h"
#include "Assets/Assets/Shader/PixelShaderAsset.h"
#include "Assets/Assets/SceneAsset.h"

namespace Eclipse::Assets
{
    using RuntimeAssetDataVariant = std::variant<
        AudioData*,
        FontData*,
        MaterialData*,
        TextureData*,
        PrefabData*,
        ShaderData*,
        SceneData*
    >;
};