#include "ComponentManager.h"

#include "DebugLogger.h"
#include "Profiler/Profiler_Macros.hpp"

namespace Eclipse
{
	void ComponentManager::Init()
	{
		myComponentData = new uint8_t[MAX_COMPONENT_MEMORY_BYTES];
	}

	void ComponentManager::OnLoadScene()
	{
		for (auto& component : myComponents)
			component->OnSceneLoaded();
	}

	void ComponentManager::AwakeStartComponents()
	{
		if (myComponentsToStart.empty())
			return;

		std::sort(myComponentsToStart.begin(), myComponentsToStart.end(), [&](Component* aComp0, Component* aComp1)
			{
				bool hasPriority = aComp0->GetUpdatePriority() > aComp1->GetUpdatePriority();
				return hasPriority;
			});

		AwakeComponents();
		StartComponents();

		myComponentsToStart.clear();
	}

	void ComponentManager::Clear()
	{
		myComponents.clear();
		delete myComponentData;

		myComponentMemoryTracker = 0;
		myNextGameobjectID = 1;
		myComponentsToStart.clear();

		for (auto& [id, obj] : myEntityIdToEntity)
		{
			delete obj;
		}

		myEntityIdToEntity.clear();
		myEntityIDToVectorOfComponentIDs.clear();

		Init();
	}

	void ComponentManager::AwakeComponents()
	{
		for (auto& component : myComponentsToStart)
			component->Awake();
	}
	void ComponentManager::StartComponents()
	{
		for (auto& component : myComponentsToStart)
			component->Start();
	}

	void ComponentManager::EditorUpdateComponents()
	{
		for (auto& component : myComponents)
			component->EditorUpdate();
	}
	void ComponentManager::EarlyUpdateComponents()
	{
		for (auto& component : myComponents)
			component->EarlyUpdate();
	}
	void ComponentManager::UpdateComponents()
	{
		for (auto& component : myComponents)
		{
			BEGIN_PROFILE_SCOPE(component->GetComponentName());
			component->Update();
			END_PROFILE_SCOPE(component->GetComponentName());
		}
	}
	void ComponentManager::LateUpdateComponents()
	{
		for (auto& component : myComponents)
			component->OnDrawGizmos();

		for (auto& component : myComponents)
			component->LateUpdate();
	}
	void ComponentManager::RenderComponents()
	{
		for (auto& component : myComponents)
			component->Render();
	}
	void ComponentManager::SortComponents()
	{
		std::sort(myComponents.begin(), myComponents.end(), [&](Component* aComp0, Component* aComp1)
			{
				return aComp0->GetUpdatePriority() > aComp1->GetUpdatePriority();
			});

		myEntityIDToVectorOfComponentIDs.clear();

		for (int i = 0; i < (int)myComponents.size()/* - 1*/; i++)
		{
			Component* comp = myComponents[i];

			auto& mapOfComponentsGO = myEntityIDToVectorOfComponentIDs[comp->gameObject->GetID()];
			RegisteredTypeIndex index = comp->myUniqueComponentID;

			mapOfComponentsGO[index] = static_cast<ComponentIndex>(i);
		}
	}
	const std::vector<Component*>& ComponentManager::GetAllComponents()
	{
		return myComponents;
	}

	std::vector<Component*> ComponentManager::GetComponents(GameObjectID aGOID)
	{
		std::vector<Component*> components;

		for (auto& component : myEntityIDToVectorOfComponentIDs.at(aGOID))
		{
			components.emplace_back(myComponents[component.second]);
		}

		return components;
	}

	bool ComponentManager::HasGameObject(GameObjectID aGOID)
	{
		return myEntityIDToVectorOfComponentIDs.find(aGOID) != myEntityIDToVectorOfComponentIDs.end();
	}

	void ComponentManager::Destroy(GameObjectID aGOID)
	{
		std::vector<int> componentsToRemove;

		for (auto& componentAtGO : myEntityIDToVectorOfComponentIDs.at(aGOID))
		{
			Component* component = myComponents[componentAtGO.second];

			component->OnDestroy();
			component->~Component();

			componentsToRemove.emplace_back(componentAtGO.second);
		}

int sizeOfComponents = myComponents.size();
int sizeOfComponentsRemove = componentsToRemove.size();
int sizeAfterRemoval = (sizeOfComponents - sizeOfComponentsRemove);

std::vector<bool> used(sizeOfComponents, false);

for (int i = 0; i < sizeOfComponentsRemove; i++)
{
	int componentIndex = componentsToRemove[i];
	int replaceIndex = sizeOfComponents - 1 - i;

	// if (sizeOfComponents - 1 - i) == to any of componentsToRemove then go back until that is not true anymore
	bool found;
	do
	{
		found = false;
		for (int j = 0; j < sizeOfComponentsRemove; j++)
		{
			if (replaceIndex == componentsToRemove[j] || used[replaceIndex])
			{
				replaceIndex--; // go back
				found = true;
				break;
			}
		}
	} while (found && replaceIndex >= 0);

	// if we didn’t find a valid replace index, skip this removal entirely
	if (replaceIndex < 0)
		continue;

	// mark as used so we don’t reuse it again later
	used[replaceIndex] = true;

	if (componentIndex > sizeAfterRemoval)
	{
		myComponents.insert(myComponents.begin() + sizeAfterRemoval, myComponents[replaceIndex]);
		sizeAfterRemoval++;
	}
	else
	{
		myComponents[componentIndex] = myComponents[replaceIndex];
	}
}

myComponents.resize(sizeAfterRemoval);

SortComponents();

int i = 0;

	}

	GameObject* ComponentManager::CreateGameObject()
	{
		GameObject* obj = new GameObject(myNextGameobjectID);
		myEntityIdToEntity[myNextGameobjectID] = obj;

		obj->AddComponent<Transform2D>();

		myNextGameobjectID++;
		return obj;
	}

	GameObject* ComponentManager::CreateGameObjectNoTransform()
	{
		GameObject* obj = new GameObject(myNextGameobjectID);
		myEntityIdToEntity[myNextGameobjectID] = obj;

		myNextGameobjectID++;
		return obj;
	}

	GameObject* ComponentManager::CreateGameObjectNoTransformWithID(GameObjectID aId)
	{
		GameObject* obj = new GameObject(aId);
		myEntityIdToEntity[aId] = obj;

		if (myNextGameobjectID <= aId) myNextGameobjectID = aId + 1;
		return obj;
	}

	void ComponentManager::BeginCollisions(GameObjectID aGOID)
	{
		auto& components = myEntityIDToVectorOfComponentIDs.at(aGOID);

		for (auto& component : components)
			for (auto& [_, componentIndex] : components)
				myComponents[componentIndex]->OnCollisionEnter();
	}
	void ComponentManager::EndCollisions(GameObjectID aGOID)
	{
		auto& components = myEntityIDToVectorOfComponentIDs.at(aGOID);

		for (auto& component : components)
			for (auto& [_, componentIndex] : components)
				myComponents[componentIndex]->OnCollisionExit();
	}
}