#pragma once

#include "AssetEngine/Managers/AssetManager.h"

#include "AssetEngine/Assets/Texture.h"


namespace Eclipse::Assets
{
	class TextureLoader;
	class TextureManager final : public AssetManager<class Textures, class Assets::TextureHandle>
	{
	public:
		Textures GetDefault();
		Textures Get(const size_t& id) override;

	protected:
		TextureLoader& GetLoader();

		void Reload(const size_t& id) override;

		Textures Load(const size_t& id) override;
		Textures ConstructAsset(const size_t& id) override;
	};
}