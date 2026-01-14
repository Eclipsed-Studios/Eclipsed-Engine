#include "SpriteAnimation.h"

#include "Models/AssetDatas/Handles/SpriteAnimationHandle.h"

namespace Eclipse
{
    size_t SpriteAnimation::GetFrameCount() const
    {
        return dataHandle->Frames.size();
    }

    const std::vector<unsigned>& SpriteAnimation::GetFrames() const
    {
        return dataHandle->Frames;
    }

    int SpriteAnimation::GetFrame(size_t aIndex) const
    {
        return dataHandle->Frames[aIndex];
    }

    const std::string& SpriteAnimation::GetAnimationNameID() const
    {
        return dataHandle->AnimationName;
    }
}