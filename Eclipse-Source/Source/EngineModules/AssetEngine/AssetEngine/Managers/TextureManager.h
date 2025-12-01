#pragma once

#include "AssetEngine/Managers/AssetManager.h"

#include "AssetEngine/Assets/Texture.h"


namespace Eclipse::Assets
{
	class TextureLoader;
	class TextureManager final : public AssetManager<class Texture, class Assets::TextureHandle>
	{
	public:
		Texture GetDefault();
		Texture Get(const size_t& id) override;

	protected:
		TextureLoader& GetLoader();

		void Reload(const size_t& id) override;

		Texture Load(const size_t& id) override;
		Texture ConstructAsset(const size_t& id) override;
	};
}