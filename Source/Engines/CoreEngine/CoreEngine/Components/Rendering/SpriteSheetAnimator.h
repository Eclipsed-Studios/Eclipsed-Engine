#pragma once

#include "../Component.h"
#include "AssetManagement/Resources/SpriteSheetAnimation.h"
#include "AssetManagement/ResourcePointer.h"

namespace ENGINE_NAMESPACE
{
    class SpriteRendrer2D;

    class SpriteSheetAnimator2D : public Component
    {
    public:
        SpriteSheetAnimator2D() = default;
        ~SpriteSheetAnimator2D() = default;

        void Start() override;
        void Update() override;

        void SetSpriteSheet(const char* aPath);

        void Play() { myIsPlaying = true; }
        void Pause() { myIsPlaying = false; }

        void SetCurrentAnimation(const char* anAnimationName);

    private:
        SpriteRenderer2D* mySpriteRenderer = nullptr;

        ResourcePointer<SpriteSheetAnimation> mySpriteSheetAnimations;
        std::string myActiveAnimation;

        float myTimePerFrame = 0.09f;
        float myTimeAccumulator = 0.f;
        int myCurrentFrame = 0;

        bool myIsPlaying = true;
    };
}