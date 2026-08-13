#include "IAssetType.h"

namespace Eclipse::Assets
{
    GUID IAssetType::GetDefaultAsset(DefaultAssetType defaultAsset) const
    {
        auto it = defaultAssetsGuids.find(defaultAsset);
        if (it == defaultAssetsGuids.end()) return {};

        return it->second;
    }
}