#include "Assets/BinaryFormats/AssetData.h"

#include "AssetDeletionQueue.h"

namespace Eclipse::Assets
{
	void AssetData::IncreaseRefCount()
	{
		refCount++;
	}

	void AssetData::DecreaseRefCount()
	{
		if (refCount <= 0)
			return;

		--refCount;

		if (refCount == 0)
		{
			AssetDeletionQueue::MarkForDelete(guid);
		}
	}
}