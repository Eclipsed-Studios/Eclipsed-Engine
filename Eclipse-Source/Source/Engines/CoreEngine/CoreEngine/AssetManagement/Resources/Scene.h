#pragma once 

#include "AssetManagement/Resources/Abstract/AbstractResource.h"

#include "ECS/ComponentManager.h"

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