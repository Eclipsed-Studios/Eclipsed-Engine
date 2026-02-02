#pragma once

#include "AssetEngine/Managers/AssetManager.h"
#include "AssetEngine/Assets/Prefab.h"
#include "AssetEngine/AssetBinaryLoader/TypeLoaders/PrefabLoader/PrefabLoader.h"


namespace Eclipse::Assets
{
	class PrefabManager final : public AssetManager<class Prefab, class Assets::PrefabHandle>
	{
	public:
		Prefab Get(const size_t& id) override;

		PrefabLoader& GetLoader();

	protected:

		void Reload(const size_t& id) override;

		Prefab Load(const size_t& id) override;
		Prefab ConstructAsset(const size_t& id) override;
	};
}