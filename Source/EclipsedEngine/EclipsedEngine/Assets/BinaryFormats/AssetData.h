#pragma once

#include <string>
#include "EclipsedEngine/Assets/Core/GUID.h"

namespace Eclipse::Assets
{
	struct AssetData {
		int refCount = 0;
		GUID guid;

		void IncreaseRefCount();
		void DecreaseRefCount();
	};
}