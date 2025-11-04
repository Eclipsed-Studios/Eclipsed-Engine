#pragma once

#include "AssetEngine/Managers/AssetManager.h"

#include "AssetEngine/Assets/Material.h"


namespace Eclipse::Assets
{
	class MaterialLoader;
	class MaterialManager final : public AssetManager<class Materials, class Assets::MaterialHandle>
	{
	public:
		Materials Get(const size_t& id) override;

		Materials GetDefault();

	protected:
		MaterialLoader& GetLoader();

		void Reload(const size_t& id) override;
		
		Materials Load(const size_t& id) override;
		Materials ConstructAsset(const size_t& id) override;
	};
}