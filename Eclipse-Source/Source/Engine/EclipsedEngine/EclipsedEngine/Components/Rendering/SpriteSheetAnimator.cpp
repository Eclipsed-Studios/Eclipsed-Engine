#include "SpriteSheetAnimator.h"

#include "SpriteRenderer2D.h"

#include "EntityEngine/ComponentManager.h"

namespace Eclipse
{
    //COMPONENT_REGISTRATION(SpriteSheetAnimator2D);

    //void SpriteSheetAnimator2D::Update()
    //{
    //    if (!myIsPlaying || !mySpriteRenderer)
    //        return;

    //    myTimeAccumulator += Time::GetDeltaTime();

    //    if (myTimeAccumulator >= myTimePerFrame)
    //    {
    //        const std::vector<unsigned>& animationFramesIdx = mySpriteSheetAnimations->GetAnimation(myActiveAnimation);
    //        if (animationFramesIdx.empty())
    //            return;

    //        myTimeAccumulator -= myTimePerFrame;

    //        if (myCurrentFrame == animationFramesIdx.size() - 1)
    //        {
    //            myCurrentFrame = 0;

    //            if (!myLoop)
    //            {
    //                myIsPlaying = false;
    //                return;
    //            }
    //        }

    //        const std::vector<Math::RectSizePos>& spriteRects = mySpriteRenderer->GetMaterial()->myTexture->GetSpriteRects();
    //        const Math::RectSizePos& rect = spriteRects[animationFramesIdx[myCurrentFrame++]];
    //        mySpriteRenderer->SetSpriteRect(rect.position, rect.position + rect.size);
    //    }
    //}

    //void SpriteSheetAnimator2D::OnSceneLoaded()
    //{
    //    SetSpriteSheet(mySpriteSheetAnimationPath->c_str());

    //    mySpriteRenderer = gameObject->GetComponent<SpriteRenderer2D>();

    //    const std::vector<Math::RectSizePos>& spriteRects = mySpriteRenderer->GetMaterial()->myTexture->GetSpriteRects();
    //    const Math::RectSizePos& rect = spriteRects[0];
    //    mySpriteRenderer->SetSpriteRect(rect.position, rect.position + rect.size);
    //}

    //void SpriteSheetAnimator2D::SetSpriteSheet(const char* aPath)
    //{
    //    mySpriteSheetAnimationPath = aPath;
    //    mySpriteSheetAnimations = Resources::Get<SpriteSheetAnimation>(aPath);

    //    //mySpriteSheet.Load(aPath);
    //    myCurrentFrame = 0;
    //    myTimeAccumulator = 0.f;
    //}

    //void SpriteSheetAnimator2D::SetCurrentAnimation(const char* anAnimationName, bool aLoop)
    //{
    //    myActiveAnimation = anAnimationName;

    //    myLoop = aLoop;
    //    myIsPlaying = true;
    //}
}