#include "ComponentManager.h"

namespace Eclipse
{
	void ComponentManager::Init()
	{
		myComponentData = new uint8_t[MAX_COMPONENT_MEMORY_BYTES];
	}

	void ComponentManager::AwakeStartComponents()
	{
		if (myComponentsToStart.empty())
			return;

		std::sort(myComponentsToStart.begin(), myComponentsToStart.end(), [&](Component* aComp0, Component* aComp1)
			{
				bool hasPriority = aComp0->myUpdateStartPriority > aComp1->myUpdateStartPriority;
				return hasPriority;
			});

		AwakeComponents();
		StartComponents();

		myComponentsToStart.clear();
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

	void ComponentManager::EarlyUpdateComponents()
	{
		for (auto& component : myComponents)
			component->EarlyUpdate();
	}
	void ComponentManager::UpdateComponents()
	{
		for (auto& component : myComponents)
			component->Update();
	}
	void ComponentManager::LateUpdateComponents()
	{
		for (auto& component : myComponents)
			component->OnDrawGizmos();

		for (auto& component : myComponents)
			component->LateUpdate();
	}
	void ComponentManager::SortSHit()
	{
		std::sort(myComponents.begin(), myComponents.end(), [&](Component* aComp0, Component* aComp1)
			{
				return aComp0->myUpdateStartPriority > aComp1->myUpdateStartPriority;
			});

		for (int i = 0; i < (int)myComponents.size()/* - 1*/; i++)
		{
			Component* comp = myComponents[i];

			auto& mapOfComponentsGO = myEntityIDToVectorOfComponentIDs.at(comp->gameObject->GetID());
			RegisteredTypeIndex index = comp->myUniqueComponentID;

			// Example: store the new position in the map
			// (this replaces your erase/swap logic)
			mapOfComponentsGO[index] = static_cast<ComponentIndex>(i);

			//Component* aComp0 = myComponents[i];
			//Component* aComp1 = myComponents[i + 1];

			//auto& mapOfComponentsGO0 = myEntityIDToVectorOfComponentIDs.at(aComp0->gameObject->GetID());
			//RegisteredTypeIndex indexComp0 = aComp0->myUniqueComponentID;
			//ComponentIndex savedValue0 = mapOfComponentsGO0.at(indexComp0);

			//auto& mapOfComponentsGO1 = myEntityIDToVectorOfComponentIDs.at(aComp1->gameObject->GetID());
			//RegisteredTypeIndex indexComp1 = aComp1->myUniqueComponentID;
			//ComponentIndex savedValue1 = mapOfComponentsGO1.at(indexComp1);

			//mapOfComponentsGO0.erase(indexComp0);
			//mapOfComponentsGO1.erase(indexComp1);

			//mapOfComponentsGO0[indexComp0] = savedValue1;
			//mapOfComponentsGO1[indexComp1] = savedValue0;
		}
	}
	const std::vector<Component*>& ComponentManager::GetComponents()
	{
		return myComponents;
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