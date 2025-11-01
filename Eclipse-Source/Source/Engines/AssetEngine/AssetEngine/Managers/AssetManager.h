#pragma once

#include <unordered_map>

namespace Eclipse
{
	template<typename AssetType, typename Handle>
	class AssetManager
	{
	public:
		virtual AssetType Get(const size_t& id) = 0;

		void Update();

	protected:
		virtual AssetType Load(const size_t& id) = 0;
		virtual AssetType ConstructAsset(const size_t& id) = 0;

	protected:
		std::unordered_map<size_t, Handle*> idToAssetHandle;
	};

	template<typename AssetType, typename Handle>
	void AssetManager<AssetType, Handle>::Update()
	{
		for (auto it = idToAssetHandle.begin(); it != idToAssetHandle.end();)
		{
			Handle* handle = it->second;

			if (!handle)
			{
				it = idToAssetHandle.erase(it);
				continue;
			}

			if (handle->refCount <= 0)
			{
				if(handle) delete handle;

				it = idToAssetHandle.erase(it);
				continue;
			}

			it++;
		}
	}
}