#include "ComponentManager.h"

#include "CoreEngine/IDGenerator.h"

#include "CoreEngine/core.h"
#include <cassert>

namespace Eclipse
{
	ComponentManager* ComponentManager::Instance;

	void ComponentManager::Init()
	{
		myComponentData = reinterpret_cast<uint8_t*>(malloc(MAX_COMPONENT_MEMORY_BYTES));
	}

	void ComponentManager::OnLoadScene()
	{
		SortUpdatePrioComponents();

		for (auto& compList : myComponents)
			SortZIndexComponents(compList);
		

		for (auto& renderLayer : myComponents)
		{
			for (auto& component : renderLayer.vector)
				component->OnSceneLoaded();
		}
	}

	void ComponentManager::OnAddedAllComponentsLoadScene()
	{
		for (auto& compList : myComponents)
			SortZIndexComponents(compList);

		for (auto& renderLayer : myComponents)
		{
			for (auto& component : renderLayer.vector)
			{
				component->OnComponentAddedNoCreations();
				component->OnComponentAdded();
			}
		}
	}

	void ComponentManager::AwakeStartComponents()
	{
		if (myComponentsToStart.empty() && myComponentsToStartBuffer.empty())
			return;

		std::sort(myComponentsToStart.begin(), myComponentsToStart.end(), [&](Component* aComp0, Component* aComp1)
			{
				bool hasPriority = aComp0->GetUpdatePriority() > aComp1->GetUpdatePriority();
				return hasPriority;
			});

		AwakeComponents();
		StartComponents();

		myComponentsToStart.clear();
		myComponentsToStart = myComponentsToStartBuffer;
		myComponentsToStartBuffer.clear();
	}

	void ComponentManager::Clear()
	{
		for (auto& renderLayer : myComponents)
		{
			for (auto& component : renderLayer.vector)
			{
				component->OnDestroy();
				component->~Component();
			}
		}

		for (auto& renderLayer : myComponents)
		{
			renderLayer.vector.clear();
		}

		myComponents.clear();

		if(myComponentData)
			free(myComponentData);

		myComponentMemoryTracker = 0;
		graveyard.clear();

		myComponentsToStartBuffer.clear();
		myComponentsToStart.clear();


		for (auto& [id, obj] : myEntityIdToEntity)
		{
			delete obj;
		}

		myEntityIdToEntity.clear();
		myEntityIDToVectorOfComponentIDs.clear();

		// TODO: MAKES NO SENSE. 
		/*WHY? -> */ Init(); // <- Made by Simon.
	}

	void ComponentManager::AwakeComponents()
	{
		for (size_t i = 0; i < myComponentsToStart.size(); ++i)
			if (myComponentsToStart[i]->myIsOwner)
				myComponentsToStart[i]->Awake();
	}

	void ComponentManager::StartComponents()
	{
		for (size_t i = 0; i < myComponentsToStart.size(); ++i)
		{
			if (myComponentsToStart[i]->myIsOwner)
			{
				myComponentsToStart[i]->Start();
				myComponentsToStart[i]->HasStarted = true;
			}
		}
	}

	void ComponentManager::EditorUpdateComponents()
	{
		CORE_PROFILE_SCOPED;

		for (auto& renderLayer : myComponents)
			for (auto& component : renderLayer.vector)
				component->EditorUpdate();
	}

	void ComponentManager::EarlyUpdateComponents()
	{
		CORE_PROFILE_SCOPED;

		for (auto& renderLayer : myComponents)
			for (auto& component : renderLayer.vector)
				if (component->HasStarted && component->myIsOwner)
					component->EarlyUpdate();
	}

	void ComponentManager::UpdateComponents()
	{
		CORE_PROFILE_SCOPED;

		for (auto& renderLayer : myComponents)
			for (int i = 0; i < renderLayer.vector.size(); i++)
				if (renderLayer.vector[i]->HasStarted && renderLayer.vector[i]->myIsOwner)
					renderLayer.vector[i]->Update();
	}

	void ComponentManager::EditorLateUpdateComponents()
	{
		CORE_PROFILE_SCOPED;

		for (auto& renderLayer : myComponents)
			for (int i = 0; i < renderLayer.vector.size(); i++)
				renderLayer.vector[i]->EditorLateUpdate();
	}

	void ComponentManager::LateUpdateComponents()
	{
		CORE_PROFILE_SCOPED;

		for (auto& renderLayer : myComponents)
			for (int i = 0; i < renderLayer.vector.size(); i++)
				renderLayer.vector[i]->OnDrawGizmos();


		for (auto& renderLayer : myComponents)
			for (int i = 0; i < renderLayer.vector.size(); i++)
				if (renderLayer.vector[i]->HasStarted && renderLayer.vector[i]->myIsOwner)
					renderLayer.vector[i]->LateUpdate();
	}

	void ComponentManager::RenderComponents()
	{
		CORE_PROFILE_SCOPED;

#ifdef ECLIPSED_EDITOR
		SortUpdatePrioComponents();
		for(auto& compList : myComponents)
			if(compList.vector.size() && compList.vector.front()->GetZIndex() >= 0)
				SortZIndexComponents(compList);
#endif
		for (auto& renderLayer : myComponents)
			for (auto& component : renderLayer.vector)
				component->Render();
	}

	void ComponentManager::SortUpdatePrioComponents()
	{
		CORE_PROFILE_SCOPED;

		// this is a work around so render components does not need to exist should be a separate list
		std::sort(myComponents.begin(), myComponents.end(), [](UpdatePriority& aComp0, UpdatePriority& aComp1)
		{
		    unsigned UpdatePriorityD0 = aComp0.Value;
			unsigned UpdatePriorityD1 = aComp1.Value;

		    return UpdatePriorityD0 > UpdatePriorityD1;
		});
	}

	void ComponentManager::SortZIndexComponents(UpdatePriority& aVec)
	{
		std::sort(aVec.vector.begin(), aVec.vector.end(), [](Component* aComp0, Component* aComp1)
			{
				float zIndex0 = aComp0->GetZIndex();
				float zIndex1 = aComp1->GetZIndex();

				return zIndex0 < zIndex1;
			});
	}

	Eclipse::Component* ComponentManager::AddComponent(GameObjectID aGOID, Eclipse::Component* (__cdecl* createFunc)(unsigned char* address), size_t size)
	{
		Component* component = AddComponentWithID(aGOID, Component::GetNextComponentID(), createFunc, size);
		component->OnComponentAdded();

		return component;
	}

	Eclipse::Component* ComponentManager::AddComponentWithID(GameObjectID aGOID, unsigned aComponentID, Eclipse::Component* (__cdecl* createFunc)(unsigned char* address), size_t size)
	{
		uint8_t* base = static_cast<uint8_t*>(myComponentData);

		uint8_t* ptrToComponent = nullptr;
		for (int i = 0; i < graveyard.size(); i++)
		{
			Graveyard& space = graveyard[i];
			if (space.size == size)
			{
				ptrToComponent = static_cast<uint8_t*>(space.ptr);
				memset(ptrToComponent, 0, space.size);

				std::swap(graveyard[i], graveyard.back());
				graveyard.pop_back();

				break;
			}
		}

		if (!ptrToComponent)
		{
			ptrToComponent = base + myComponentMemoryTracker;

			myComponentMemoryTracker += size;

			assert((myComponentMemoryTracker) <= MAX_COMPONENT_MEMORY_BYTES && "Adding the latest componnet made the component tracker go over max count increase MAX_COMPONENT_MEMORY_BYTES");
		}


		unsigned typeIndex = Utilities::IDGenerator::GetID();

		if (myEntityIdToEntity.find(aGOID) == myEntityIdToEntity.end())
			myEntityIdToEntity[aGOID] = CreateGameObject(aGOID);

#ifdef ECLIPSED_NETWORKING
		BeforeComponentConstruction();
#endif

		Eclipse::Component* component = createFunc(ptrToComponent);
		component->componentSize = size;

		component->SetComponentID(aComponentID);

#ifdef ECLIPSED_NETWORKING
		AfterComponentConstruction();
#endif

		component->gameObject = myEntityIdToEntity.at(aGOID);
		component->myComponentComponentID = typeIndex;

		myComponentsToStartBuffer.emplace_back(component);


		bool SetComponentPtr = false;
		UpdatePriority* componentVectorPtr = nullptr;
		for (auto& componentVec : myComponents)
		{
			if (componentVec.Value == component->GetUpdatePriority())
			{
				componentVectorPtr = &componentVec;
				SetComponentPtr = true;
				break;
			}
		}
		if (!SetComponentPtr)
		{
			componentVectorPtr = &myComponents.emplace_back();
			componentVectorPtr->Value = component->GetUpdatePriority();
		}

		componentVectorPtr->vector.push_back(component);

		if (SetComponentPtr)
		{
			if (component->GetZIndex() >= 0)
				SortZIndexComponents(*componentVectorPtr);

			SortUpdatePrioComponents();
		}

		size_t componentIndex = myComponents.size() - 1;

		myEntityIDToVectorOfComponentIDs[aGOID].emplace_back(component);
		//component->myComponentIndex = componentIndex;

		//CreateComponentReplicated(component);

		if (myComponents.size() <= 1)
			return component;

		return component;
	}

	inline void ComponentManager::DeleteComponent(unsigned aGOID, unsigned aUniqueComponentID, unsigned aComponentID)
	{
		if (myEntityIDToVectorOfComponentIDs.find(aGOID) == myEntityIDToVectorOfComponentIDs.end())
			return;

		auto& entityIDComponents = myEntityIDToVectorOfComponentIDs.at(aGOID);

		bool DeletedAComponent = false;
		unsigned indexToDelete = 0;
		for (int i = 0; i < entityIDComponents.size(); i++)
		{
			Component* component = entityIDComponents[i];


			if (component->myInstanceComponentID != aComponentID)
				continue;

			component->OnDestroy();
			component->~Component();

			graveyard.emplace_back(component, component->componentSize);

			component->IsDeleted = true;

			DeleteReplicatedComponent(aComponentID);

			indexToDelete = i;

			DeletedAComponent = true;

			break;
		}

		if (!DeletedAComponent)
			return;

		entityIDComponents[indexToDelete] = entityIDComponents.back();
		entityIDComponents.pop_back();

		bool FoundDeleted = false;

		UpdatePriority* vectorPtr;
		for (auto& renderLayer : myComponents)
		{
			for (auto& component : renderLayer.vector)
			{
				if (component->IsDeleted)
				{
					component = renderLayer.vector.back();
					FoundDeleted = true;

					vectorPtr = &renderLayer;

					break;
				}
			}

			if (FoundDeleted)
				renderLayer.vector.pop_back();
		}

		SortZIndexComponents(*vectorPtr);
	}

	GameObject* ComponentManager::FindObjectByName(const char* aName)
	{
		for (auto& [id, gameobject] : myEntityIdToEntity)
		{
			if (!gameobject)
				continue;

			if (gameobject->GetName() == aName)
			{
				return gameobject;
			}
		}

		return nullptr;
	}

	const Eclipse::ComponentManager::RenderLayers& ComponentManager::GetAllComponents()
	{
		return myComponents;
	}

	std::vector<Component*> ComponentManager::GetComponents(GameObjectID aGOID)
	{
		if (myEntityIDToVectorOfComponentIDs.find(aGOID) == myEntityIDToVectorOfComponentIDs.end())
			return {};

		return myEntityIDToVectorOfComponentIDs.at(aGOID);
	}

	bool ComponentManager::HasGameObject(GameObjectID aGOID)
	{
		return myEntityIdToEntity.find(aGOID) != myEntityIdToEntity.end();
	}

	GameObject* ComponentManager::GetGameObject(unsigned aGOID)
	{
		if (myEntityIdToEntity.find(aGOID) == myEntityIdToEntity.end())
			return nullptr;

		return myEntityIdToEntity.at(aGOID);
	}

	void ComponentManager::CommitDestroy()
	{
		if (gameobjectsToRemove.empty())
			return;

		unsigned componentsDeleted = 0;
		for (int goID : gameobjectsToRemove)
		{
			// This has tyo be checked only because Gameobjects can exist without components
			if (myEntityIDToVectorOfComponentIDs.find(goID) == myEntityIDToVectorOfComponentIDs.end())
				continue;

			for (auto& component : myEntityIDToVectorOfComponentIDs.at(goID))
			{
				if (!component)
					continue;

#ifdef ECLIPSED_NETWORKING
				DeleteReplicatedComponent(component->myInstanceComponentID);
#endif
				component->IsDeleted = true;

				component->OnDestroy();
				component->~Component();

				graveyard.emplace_back(component, component->componentSize);

				component = nullptr;

				componentsDeleted++;
			}

			myEntityIDToVectorOfComponentIDs.erase(goID);
		}

		std::vector<UpdatePriority*> componentListsToSort;
		for (auto& renderLayer : myComponents)
		{
			for (int i = 0; i < renderLayer.vector.size(); i++)
			{
				auto& component = renderLayer.vector[i];
				if (!component || component->IsDeleted)
				{
					Component* backComponent = renderLayer.vector.back();

					if (backComponent && !backComponent->IsDeleted)
						std::swap(renderLayer.vector[i], renderLayer.vector.back());

					renderLayer.vector.pop_back();

					componentListsToSort.push_back(&renderLayer);

					i--;
				}
			}
		}

		{
			int componentToStartSize = 0;
			for (int i = myComponentsToStart.size() - 1; i >= 0; i--)
			{
				auto& component = myComponentsToStart[i];
				if (component->IsDeleted)
				{
					std::swap(component, myComponentsToStart[myComponentsToStart.size() - componentToStartSize - 1]);
					componentToStartSize++;
				}
			}
			myComponentsToStart.resize(myComponentsToStart.size() - componentToStartSize);
		}

		{
			int componentToStartSize = 0;
			for (int i = myComponentsToStartBuffer.size() - 1; i >= 0; i--)
			{
				auto& component = myComponentsToStartBuffer[i];
				if (component->IsDeleted)
				{
					std::swap(component, myComponentsToStartBuffer[myComponentsToStartBuffer.size() - componentToStartSize - 1]);
					componentToStartSize++;
				}
			}
			myComponentsToStartBuffer.resize(myComponentsToStartBuffer.size() - componentToStartSize);
		}

		for(auto& components : componentListsToSort)
			SortZIndexComponents(*components);

		for (int goID : gameobjectsToRemove)
		{
			if (!myEntityIdToEntity.contains(goID))
				continue;

			delete myEntityIdToEntity.at(goID);
			myEntityIdToEntity.erase(goID);
		}

		gameobjectsToRemove.clear();
	}

	void ComponentManager::Destroy(GameObjectID aGOID)
	{
#ifdef ECLIPSED_NETWORKING
		DestroyGameObjectReplicated(aGOID);
#endif

		GameObject* gameobject = myEntityIdToEntity.at(aGOID);
		if (gameobject)
			gameobjectsToRemove.emplace_back(aGOID);

		auto& children = gameobject->GetChildren();
		for (auto& child : children)
			Destroy(child->GetID());
	}

	GameObject* ComponentManager::CreateGameObject(GameObjectID aId)
	{
		GameObject* obj = new GameObject(aId);
		myEntityIdToEntity[aId] = obj;

		return obj;
	}

	GameObject* ComponentManager::CreateGameObject()
	{
		unsigned randomID = GetNewGOID();
		GameObject* obj = new GameObject(randomID);
		myEntityIdToEntity[randomID] = obj;

		return obj;
	}


	void ComponentManager::BeginCollisions(GameObjectID aGOID)
	{
		auto& allComponents = myEntityIDToVectorOfComponentIDs[aGOID];

		for (int i = 0; i < allComponents.size(); i++)
			allComponents[i]->OnCollisionEnter();
	}

	void ComponentManager::EndCollisions(GameObjectID aGOID)
	{
		auto& allComponents = myEntityIDToVectorOfComponentIDs[aGOID];

		for (int i = 0; i < allComponents.size(); i++)
			allComponents[i]->OnCollisionExit();
	}
}
