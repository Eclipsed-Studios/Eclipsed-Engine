#pragma once

#include "AssetEngine/AssetBinaryLoader/TypeLoaders/TypeLoader.h"
#include "AssetEngine/Models/AssetDatas/Handles/SpriteAnimationHandle.h"


namespace Eclipse::Assets
{
	class SpriteAnimationLoader : public TypeLoader<SpriteAnimationHandle>
	{
	public:
		SpriteAnimationHandle* Load(const size_t& id) override;
		void Load(const size_t& id, SpriteAnimationHandle* handle) override;
	};
}