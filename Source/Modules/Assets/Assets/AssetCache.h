#pragma once

#include <unordered_map>

#include "Core/SupportedAssets.h"
#include "Core/GUID.h"

#include "BinaryFormats/AssetData.h"

namespace Eclipse::Assets
{
	class AssetCache
	{
	public:
		static AssetData* Get(GUID guid);
		static AssetData* Store(GUID guid, AssetData* data);
		static void Delete(GUID guid);

		static void MarkForReload(GUID guid);
		static void ProcessReloads();

	private:
		static inline std::vector<GUID> pendingReload;
		static inline std::unordered_map<GUID, AssetData*, GUIDHash> loadedAssets;
	};
}