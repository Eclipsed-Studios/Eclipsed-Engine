#pragma once

#include "AssetData.h"
#include "Core/Math/Vector/Vector2.h"

namespace Eclipse
{
	class GameObject;
}


namespace Eclipse::Assets
{
	struct PrefabData : public AssetData {
		GameObject* gameobject = nullptr;
		char* data;

		~PrefabData()
		{
			free(data);
		}
	};
}