#pragma once

#include "ComponentManager.h"

namespace Eclipse
{
	template <typename T>
	inline T* GetComponent(unsigned aGOID)
	{
		return ComponentManager::GetComponent<T>(aGOID);
	}

	template <typename T>
	inline T* AddComponent(unsigned aGOID)
	{
		return ComponentManager::AddComponent<T>(aGOID);
	}

	template <typename T>
	inline void RemoveComponent(unsigned aGOID)
	{
		ComponentManager::RemoveComponent<T>(aGOID);
	}

	inline GameObject* Instantiate()
	{
		return ComponentManager::CreateGameObject();
	}

	inline GameObject* CreateGameObject()
	{
		return ComponentManager::CreateGameObject();
	}
}