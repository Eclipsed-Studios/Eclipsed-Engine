#pragma once

#include "Asset.h"

namespace Eclipse
{
	namespace Assets
	{
		struct SpriteAnimationHandle;
		class AnimationManager;
	}

	class SpriteAnimation final
	{
		ASSET_OPERATORS_DEF(SpriteAnimation, Assets::SpriteAnimationHandle, Assets::AnimationManager);

	public:
		size_t GetFrameCount() const;
		const std::vector<unsigned>& GetFrames() const;
		int GetFrame(size_t aIndex) const;

		const std::string& GetAnimationNameID() const;
	};
}