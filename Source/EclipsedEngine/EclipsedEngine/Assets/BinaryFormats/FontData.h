#pragma once

#include "AssetData.h"

#include "EclipsedEngine/Core/Math/Vector/Vector2.h"
#include <unordered_map>

namespace Eclipse::Assets
{
    struct Character
    {
        unsigned textureID;
        Math::Vector2i size;
        Math::Vector2i bearing;
        int advance;
    };

    struct FontData : public AssetData {
        std::unordered_map<char, Character> myCharTexture;
        float maxCharHeight;
    };
}
