#include "SpriteSheetAnimator.h"

#include "SpriteRendrer2D.h"

#include "Timer.h"
#include "ECS/ComponentManager.h"

namespace ENGINE_NAMESPACE
{
    void SpriteSheetAnimator2D::Update()
    {
        if (!myIsPlaying || !mySpriteRenderer)
            return;

        myTimeAccumulator += Time::GetDeltaTime();

        if (myTimeAccumulator >= myTimePerFrame)
        {
            const std::vector<unsigned>& animationFramesIdx = mySpriteSheetAnimations->GetAnimation(myActiveAnimation);

            myTimeAccumulator -= myTimePerFrame;
            myCurrentFrame = (myCurrentFrame + 1) % animationFramesIdx.size();

            const Math::Rect& rect = mySpriteSheetAnimations->GetRect(animationFramesIdx[myCurrentFrame]);
            mySpriteRenderer->SetSpriteRect(rect.min, rect.max);
        }
    }

    void SpriteSheetAnimator2D::Start()
    {
        mySpriteRenderer = ComponentManager::GetComponent<SpriteRendrer2D>(gameObject);

        const Math::Rect& rect = mySpriteSheetAnimations->GetRect(0);
        mySpriteRenderer->SetSpriteRect(rect.min, rect.max);
    }

    void SpriteSheetAnimator2D::SetSpriteSheet(const char* aPath)
    {
        mySpriteSheetAnimations = Resources::Get<SpriteSheetAnimation>(aPath);

        //mySpriteSheet.Load(aPath);
        myCurrentFrame = 0;
        myTimeAccumulator = 0.f;
    }
    void SpriteSheetAnimator2D::SetCurrentAnimation(const char* anAnimationName)
    {
        myActiveAnimation = anAnimationName;
    }
}