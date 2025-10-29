#pragma once

namespace Eclipse::Assets
{
	struct AssetHandle
	{
		int refCount = 0;
		size_t assetID = 0;
	};
};