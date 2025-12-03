#pragma once

#include "AssetEngine/Managers/AssetManager.h"

#include "AssetEngine/Assets/Material.h"


namespace Eclipse::Assets
{
	class MaterialLoader;
	class MaterialManager final : public AssetManager<class Material, class Assets::MaterialHandle>
	{
	public:
		Material Get(const size_t& id) override;

		Material GetDefault();

	protected:
		MaterialLoader& GetLoader();

		void Reload(const size_t& id) override;
		
		Material Load(const size_t& id) override;
		Material ConstructAsset(const size_t& id) override;
	};
}