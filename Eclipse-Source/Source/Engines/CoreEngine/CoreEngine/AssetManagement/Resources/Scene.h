#pragma once 

#include "CoreEngine/AssetManagement/Resources/Abstract/AbstractResource.h"

#include "EntityEngine/ComponentManager.h"

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