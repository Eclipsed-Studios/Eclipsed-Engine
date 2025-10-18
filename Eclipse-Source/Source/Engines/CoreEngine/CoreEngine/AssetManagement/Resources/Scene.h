#pragma once 

#include "../CoreEngine/CoreEngine/AssetManagement/Resources/Abstract/AbstractResource.h"

#include "../CoreEngine/CoreEngine/ECS/ComponentManager.h"

namespace Eclipse
{
	class Scene
	{
	public:
		std::string relativePath;
		std::string sceneName;
		ComponentManager myComponentManager;
	};
}