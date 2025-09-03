#pragma once

#include <vector>
#include "Math/Vector/Vector2.h"

namespace ENGINE_NAMESPACE
{
    struct SpriteSheetRect
    {
        Math::Vector2f min;
        Math::Vector2f max;
    };

    class SpriteSheet
    {
    public:
        SpriteSheet() = default;
        ~SpriteSheet() = default;

        void Load(const char* aPath);
        void Save(const char* aPath);

        const std::vector<SpriteSheetRect>& GetSpriteRecs() const { return mySpriteRects; };

    private:
        std::vector<SpriteSheetRect> mySpriteRects;
    };
}