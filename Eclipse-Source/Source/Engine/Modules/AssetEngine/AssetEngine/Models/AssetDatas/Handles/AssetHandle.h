#pragma once

namespace Eclipse::Assets
{
	struct AssetHandle
	{
		size_t assetID;
		int refCount = 0;
	};
};