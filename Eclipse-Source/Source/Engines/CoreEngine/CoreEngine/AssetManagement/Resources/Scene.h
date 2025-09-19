#pragma once 

#include "AssetManagement/Resources/Abstract/AbstractResource.h"

#include "ECS/ComponentManager.h"

namespace Eclipse
{
	class Scene : public AbstractResource
	{
		BASE_RESOURCE(Scene)

	public:


	private:
		std::string sceneName;
		ComponentManager myComponentManager;
	};
}