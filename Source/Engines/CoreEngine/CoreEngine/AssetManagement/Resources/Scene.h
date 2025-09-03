#pragma once 

#include "AssetManagement/Resources/Abstract/AbstractResource.h"

#include "ECS/ComponentManager.h"

namespace ENGINE_NAMESPACE
{
	class Scene : public AbstractResource
	{
		BASE_RESOURCE(Scene)

	public:
		ComponentManager& GetComponentManager();

	private:
		void Setup();


	private:
		ComponentManager myComponentManager = {};
	};
}