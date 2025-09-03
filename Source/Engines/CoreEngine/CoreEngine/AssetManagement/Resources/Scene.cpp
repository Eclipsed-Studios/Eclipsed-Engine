#include "Scene.h"

#include "AssetManagement/Resources/Abstract/AbstractResource.h"

#include "ECS/ComponentManager.h"

namespace ENGINE_NAMESPACE
{
	void Scene::Setup()
	{
		myComponentManager.Init();
	}
	ComponentManager& Scene::GetComponentManager()
	{
		return myComponentManager;
	}
}