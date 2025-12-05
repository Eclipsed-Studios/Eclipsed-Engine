#include "ComponentManager.h"

#include "CoreEngine/IDGenerator.h"

namespace Eclipse
{
	void ComponentManager::Init()
	{
		myComponentData = new uint8_t[MAX_COMPONENT_MEMORY_BYTES];
	}

	void ComponentManager::OnLoadScene()
	{
		for (Component* component : myComponents)
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
		for (auto& component : myComponents)
		{
			component->OnDestroy();
			component->~Component();
		}

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
			component->Update();
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
			RegisteredTypeIndex index = comp->myComponentComponentID;

			mapOfComponentsGO[index] = static_cast<ComponentIndex>(i);
		}
	}
	
	Eclipse::Component* ComponentManager::AddComponent(GameObjectID aGOID, Eclipse::Component* (__cdecl* createFunc)(unsigned char* address), size_t size)
	{
		uint8_t* base = static_cast<uint8_t*>(myComponentData);
		uint8_t* ptrToComponent = base + myComponentMemoryTracker;
		size_t sizeOfNewComponent = size;
		myComponentMemoryTracker += sizeOfNewComponent;

		assert(myComponentMemoryTracker <= MAX_COMPONENT_MEMORY_BYTES && "MAX_COMPONENT_MEMORY_BYTES needs to be increased to add more components");

		unsigned typeIndex = Utilities::IDGenerator::GetID();

		if (myEntityIdToEntity.find(aGOID) == myEntityIdToEntity.end())
		{
			myEntityIdToEntity[aGOID] = CreateGameObject();
		}

		Eclipse::Component* component = createFunc(ptrToComponent);
		component->SetComponentID();
		component->gameObject = myEntityIdToEntity[aGOID];
		component->myComponentComponentID = typeIndex;

		component->OnComponentAdded();

		myComponentsToStart.emplace_back(component);

		myComponents.emplace_back(component);
		size_t componentIndex = myComponents.size() - 1;

		myEntityIDToVectorOfComponentIDs[aGOID][typeIndex] = componentIndex;
		myComponents.back()->myComponentIndex = componentIndex;

		if (myComponents.size() <= 1)
			return component;

		SortComponents();

		return component;
	}

	Eclipse::Component* ComponentManager::AddComponentWithID(GameObjectID aGOID, unsigned aComponentID, Eclipse::Component* (__cdecl* createFunc)(unsigned char* address), size_t size)
	{
		uint8_t* base = static_cast<uint8_t*>(myComponentData);
		uint8_t* ptrToComponent = base + myComponentMemoryTracker;
		myComponentMemoryTracker += size;

		unsigned typeIndex = Utilities::IDGenerator::GetID();

		if (myEntityIdToEntity.find(aGOID) == myEntityIdToEntity.end())
		{
			myEntityIdToEntity[aGOID] = CreateGameObject();
		}

		Eclipse::Component* component = createFunc(ptrToComponent);
		component->SetComponentID(aComponentID);
		component->gameObject = myEntityIdToEntity[aGOID];
		component->myComponentComponentID = typeIndex;

		myComponentsToStart.emplace_back(component);

		myComponents.emplace_back(component);
		size_t componentIndex = myComponents.size() - 1;

		myEntityIDToVectorOfComponentIDs[aGOID][typeIndex] = componentIndex;
		myComponents.back()->myComponentIndex = componentIndex;

		if (myComponents.size() <= 1)
			return component;

		SortComponents();

		return component;
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
						replaceIndex--;
						found = true;
						break;
					}
				}
			} while (found && replaceIndex >= 0);

			if (replaceIndex < 0)
				continue;

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

		delete myEntityIdToEntity.at(aGOID);
		myEntityIdToEntity.erase(aGOID);

		int i = 0;

	}

	GameObject* ComponentManager::CreateGameObject(GameObjectID aId)
	{
		if (aId == 0) aId = myNextGameobjectID;

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