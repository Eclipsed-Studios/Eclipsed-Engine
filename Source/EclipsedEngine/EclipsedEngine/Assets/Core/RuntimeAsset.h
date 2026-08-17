#pragma once

#include <variant>

#include "EclipsedEngine/Assets/Assets/TextureAsset.h"
#include "EclipsedEngine/Assets/Assets/PrefabAsset.h"
#include "EclipsedEngine/Assets/Assets/MaterialAsset.h"
#include "EclipsedEngine/Assets/Assets/FontAsset.h"
#include "EclipsedEngine/Assets/Assets/AudioAsset.h"
#include "EclipsedEngine/Assets/Assets/Shader/VertexShaderAsset.h"
#include "EclipsedEngine/Assets/Assets/Shader/PixelShaderAsset.h"
#include "EclipsedEngine/Assets/Assets/SceneAsset.h"

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