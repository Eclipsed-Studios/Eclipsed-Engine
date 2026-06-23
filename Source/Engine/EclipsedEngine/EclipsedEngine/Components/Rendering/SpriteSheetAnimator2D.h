#pragma once

#include "EclipsedEngine/Components/Component.h"
#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"

//#include "AssetEngine/Assets/SpriteAnimation.h"

ECLIPSED_CLASS;

namespace Eclipse
{
    class SpriteRenderer2D;

    class ECLIPSED_API SpriteSheetAnimator2D : public Component
    {
        BASE_SELECTION(SpriteSheetAnimator2D, 10)

    public:
        void OnComponentAdded() override;

        void Update() override;

        void SetSpriteSheet(const char* aPath);

        void Play() { myIsPlaying = true; }
        void Pause() { myIsPlaying = false; }

        void SetIsLooping(bool IsLooping) { myLoop = IsLooping; }

        void SetCurrentAnimation(const char* anAnimationName, bool aLoop = true);

//#ifdef ECLIPSED_EDITOR
//        void SetFirstSpriteSheet();
//        bool isUsingspritesheet = true;
//#endif
    private:

        //SERIALIZED_FIELD_DEFAULT(std::string, mySpriteSheetAnimationPath, "");

    private:
        std::vector<unsigned> TemporarySpriteAnimation{ 0,1,2,3 };

        SpriteRenderer2D* mySpriteRenderer;
        std::string myActiveAnimation;

        float myTimePerFrame = 0.04f;
        float myTimeAccumulator = 0.f;

        int myCurrentFrame = 0;
        bool myLoop = true;

        bool myIsPlaying = true;
    };
}