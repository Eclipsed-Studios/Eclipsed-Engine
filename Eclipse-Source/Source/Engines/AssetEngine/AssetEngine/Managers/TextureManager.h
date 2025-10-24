#pragma once

#include "AssetEngine/Managers/AssetManager.h"

#include "AssetEngine/Assets/Texture.h"


namespace Eclipse::Assets
{
	class TextureManager final : public AssetManager<class Textures, class Assets::TextureHandle>
	{
	public:
		Textures Get(const size_t& id) override;

	protected:
		Textures Load(const size_t& id) override;
		Textures ConstructAsset(const size_t& id) override;
	};
}