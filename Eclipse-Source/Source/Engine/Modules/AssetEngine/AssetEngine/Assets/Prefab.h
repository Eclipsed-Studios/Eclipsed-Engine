#pragma once

#include "Asset.h"


namespace Eclipse
{
	namespace Assets
	{
		struct PrefabHandle;
		class PrefabManager;
	}

	class Prefab final
	{
		ASSET_OPERATORS_DEF(Prefab, Assets::PrefabHandle, Assets::PrefabManager);
	};
}