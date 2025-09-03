#include "Animation2D.h"

#include "SpriteRendrer2D.h"

#include "Timer.h"
#include "ECS/ComponentManager.h"

namespace ENGINE_NAMESPACE
{
    void Animation2D::Update()
    {
        myTimeAccumulator += Time::GetDeltaTime();

        if (myTimeAccumulator >= myTimePerFrame)
        {
            const std::vector<SpriteSheetRect>& spriteSheetFrames = mySpriteSheet.GetSpriteRecs();

            myTimeAccumulator -= myTimePerFrame;
            myCurrentFrame = (myCurrentFrame + 1) % spriteSheetFrames.size();

            const SpriteSheetRect& rect = spriteSheetFrames[myCurrentFrame];
            mySpriteRenderer->SetSpriteRect(rect.min, rect.max);
        }
    }

    void Animation2D::Start()
    {
        mySpriteRenderer = ComponentManager::GetComponent<SpriteRendrer2D>(gameObject);
    }

    void Animation2D::SetSpriteSheet(const char* aPath)
    {
        mySpriteSheet.Load(aPath);
        myCurrentFrame = 0;
        myTimeAccumulator = 0.f;

        if (mySpriteRenderer && !mySpriteSheet.GetSpriteRecs().empty())
        {
            const SpriteSheetRect& rect = mySpriteSheet.GetSpriteRecs()[0];
            mySpriteRenderer->SetSpriteRect(rect.min, rect.max);
        }
    }
}