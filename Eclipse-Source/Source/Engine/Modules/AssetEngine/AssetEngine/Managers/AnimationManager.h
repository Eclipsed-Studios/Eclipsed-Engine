#pragma once

#include "AssetEngine/Managers/AssetManager.h"
#include "AssetEngine/Assets/SpriteAnimation.h"


namespace Eclipse::Assets
{
	class AnimationLoader;
	class AnimationManager final : public AssetManager<class SpriteAnimation, class Assets::SpriteAnimationHandle>
	{
	public:
		SpriteAnimation Get(const size_t& id) override;

	protected:
		void Reload(const size_t& id) override;

		SpriteAnimation Load(const size_t& id) override;
		SpriteAnimation ConstructAsset(const size_t& id) override;
	};
}