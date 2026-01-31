#pragma once

#include "AssetHandle.h"

#include <string>

namespace Eclipse
{
	class GameObject;
}

namespace Eclipse::Assets 
{
	struct PrefabHandle : public AssetHandle
	{
		GameObject* gameobject;
		char* data;
		
		~PrefabHandle()
		{
			free(data);
		}
	};
};