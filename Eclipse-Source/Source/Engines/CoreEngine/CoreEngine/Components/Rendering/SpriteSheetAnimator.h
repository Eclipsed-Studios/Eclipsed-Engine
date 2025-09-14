#pragma once

#include "Components/Base/BaseComponent.h"

#include "AssetManagement/Resources/SpriteSheetAnimation.h"
#include "AssetManagement/ResourcePointer.h"
#include "ECS/ComponentManager.h"

namespace Eclipse
{
    class SpriteRendrer2D;

    class SpriteSheetAnimator2D : public Component
    {
        BASE_SELECTION(SpriteSheetAnimator2D, 0)

    public:
        void Start() override;
        void Update() override;

        void SetSpriteSheet(const char* aPath);

        void Play() { myIsPlaying = true; }
        void Pause() { myIsPlaying = false; }

        void SetCurrentAnimation(const char* anAnimationName, bool aLoop = true);

    protected:
        void DrawInspector() override;

    private:
        SpriteRenderer2D* mySpriteRenderer = nullptr;

        ResourcePointer<SpriteSheetAnimation> mySpriteSheetAnimations;

        ReflectedVar_Default(std::string, mySpriteSheetAnimationPath, "");

    private:
        std::string myActiveAnimation;

        float myTimePerFrame = 0.04f;
        float myTimeAccumulator = 0.f;
        int myCurrentFrame = 0;

        bool myIsPlaying = false;
        bool myLoop = true;
    };
}