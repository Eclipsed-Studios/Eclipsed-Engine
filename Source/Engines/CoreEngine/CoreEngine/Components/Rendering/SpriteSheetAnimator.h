#pragma once

#include "../Component.h"
#include "SpriteSheet.h"

namespace ENGINE_NAMESPACE
{
    class SpriteRendrer2D;

    class Animation2D : public Component
    {
    public:
        Animation2D() = default;
        ~Animation2D() = default;

        void Start() override;
        void Update() override;

        void SetSpriteSheet(const char* aPath);

        void Play() { myIsPlaying = true; }
        void Pause() { myIsPlaying = false; }

    private:
        SpriteRendrer2D* mySpriteRenderer = nullptr;

        SpriteSheet mySpriteSheet;

        float myTimePerFrame = 0.1f;
        float myTimeAccumulator = 0.f;
        int myCurrentFrame = 0;

        bool myIsPlaying = true;
    };
}