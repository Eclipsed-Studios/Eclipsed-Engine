#pragma once

#include "EntityEngine/Component.h"
#include "EntityEngine/GameObject.h"

#include <vector>

#include <unordered_map>

#include "CoreEngine/Macros/defines.h"

#include <functional>

#define GetComp(Type, GOID)\
ComponentManager::Get().GetComponent<Type>(GOID)

#define MAX_COMPONENT_MEMORY_BYTES 20'000'000
#define MAX_COMPONENTSARRAY MAX_COMPONENT_MEMORY_BYTES / 100

namespace Eclipse
{
	namespace Editor {
		class HierarchyWindow;
		class InspectorWindow;
		class GameObjectInspector;
		class EditorActions;
	}

	typedef unsigned ComponentIndex;

	class GameObject;
	class Component;
	class ECLIPSED_API ComponentManager
	{
		friend class Editor::EditorActions;
		friend class Editor::HierarchyWindow;
		friend class Editor::GameObjectInspector;
		friend class Editor::InspectorWindow;
		friend class SceneLoader;

	public:
		template<typename T>
		struct FloatVectorContainer
		{
			unsigned Value = 0;
			std::vector<T> vector;
		};

		typedef FloatVectorContainer<Component*> UpdatePriority;
		typedef std::vector<UpdatePriority> RenderLayers;

		static ComponentManager* Instance;
		static ComponentManager& Get()
		{
			return *Instance;
		}

		void SetIntance(ComponentManager& aComponentManager) { Instance = &aComponentManager; }

		ComponentManager() = default;
		~ComponentManager() = default;

		void SetCreateComponentReplicated(std::function<void(Component*)> aCreateComponentReplicated) { CreateComponentReplicated = aCreateComponentReplicated; }

		void SetDeleteReplicationComponent(std::function<void(unsigned)> aDeleteReplicatedComponent) { DeleteReplicatedComponent = aDeleteReplicatedComponent; }
		void SetDestroyGameObjectReplicated(std::function<void(unsigned)> aDestroyGameObjectReplicated) { DestroyGameObjectReplicated = aDestroyGameObjectReplicated; }

		void SetBeforeAfterComponentConstruction(std::function<void()> aBeforeComponentConstruction, std::function<void()> aAfterComponentConstruction)
		{
			BeforeComponentConstruction = aBeforeComponentConstruction;
			AfterComponentConstruction = aAfterComponentConstruction;
		}

		void Init();

		void OnAddedAllComponentsLoadScene();
		void OnLoadScene();

		void AwakeStartComponents();

		void AwakeComponents();
		void StartComponents();

		void EditorUpdateComponents();
		void EditorLateUpdateComponents();

		void EarlyUpdateComponents();
		void UpdateComponents();
		void LateUpdateComponents();
		void RenderComponents();

		void SortUpdatePrioComponents();
		void SortZIndexComponents(UpdatePriority& aVec);
		
		//void SortRenderComponents();

		void BeginCollisions(unsigned aGOID);
		void EndCollisions(unsigned aGOID);

		template <typename T>
		void GetAllComponentsOfTypePtr(std::vector<int>& aComponents);
		
		template <typename T>
		void GetAllComponentsOfType(unsigned aGOID, std::vector<T*>& aComponents);

		template <typename T>
		T* GetComponent(unsigned aGOID);

		template <typename T>
		T* AddComponent(unsigned aGOID, bool IsReplicated = false);
		template <typename T>
		T* AddComponentWithID(unsigned aGOID, unsigned aComponentID, bool IsReplicated = false);

		void DeleteComponent(unsigned aGOID, unsigned aUniqueComponentID, unsigned aComponentID);

		GameObject* FindObjectByName(const char* aName);


		Component* AddComponent(unsigned aGOID, Eclipse::Component* (__cdecl* createFunc)(unsigned char* address), size_t size);
		Component* AddComponentWithID(unsigned aGOID, unsigned aComponentID, Eclipse::Component* (__cdecl* createFunc)(unsigned char* address), size_t size);


		template <typename T>
		unsigned GetComponentID();

		const Eclipse::ComponentManager::RenderLayers& GetAllComponents();

		std::vector<Component*> GetComponents(unsigned aGOID);


		bool HasGameObject(unsigned aGOID);
		GameObject* GetGameObject(unsigned aGOID);

		void CommitDestroy();

		void Destroy(unsigned aGOID);

		unsigned GetNewGOID()
		{
			return Random::RandRange<unsigned>(0, 0x00FFFFFF);
		}

		GameObject* CreateGameObject(GameObjectID aId);
		GameObject* CreateGameObject();

		void Clear();

	private:
		std::function<void(Component*)> CreateComponentReplicated;

		std::function<void()> BeforeComponentConstruction;
		std::function<void()> AfterComponentConstruction;

		std::function<void(unsigned)> DestroyGameObjectReplicated;
		std::function<void(unsigned)> DeleteReplicatedComponent;


		size_t myComponentMemoryTracker = 0;
		uint8_t* myComponentData = nullptr;

		//std::vector<Component*> myRenderComponents;

		RenderLayers myComponents;

		std::vector<Component*> myComponentsToStartBuffer;
		std::vector<Component*> myComponentsToStart;

		// Gameobject to components
		std::unordered_map<unsigned, GameObject*> myEntityIdToEntity;
		std::unordered_map<unsigned, std::vector<Component*>> myEntityIDToVectorOfComponentIDs;

		std::vector<unsigned> gameobjectsToRemove;

		struct Graveyard
		{
			void* ptr;
			size_t size;
		};
		std::vector<Graveyard> graveyard;
	};
}

#include "ComponentManager.inl"