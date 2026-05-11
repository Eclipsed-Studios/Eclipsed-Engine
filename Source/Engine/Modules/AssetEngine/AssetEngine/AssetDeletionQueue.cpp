#include "AssetDeletionQueue.h"

namespace Eclipse::Assets
{
	void AssetDeletionQueue::MarkForDelete(GUID guid)
	{
		pendingForDelete.push_back(guid);
	}

	void AssetDeletionQueue::ProcessPendingForDelete()
	{
	}
}