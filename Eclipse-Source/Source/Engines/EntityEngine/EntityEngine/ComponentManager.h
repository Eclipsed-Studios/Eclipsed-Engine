#pragma once

#include "Components/Base/Component.h"
#include "EntityEngine/GameObject.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <typeindex>
#include <assert.h>

#define GetComp(Type, GOID)\
ComponentManager::GetComponent<Type>(GOID)

#define MAX_COMPONENT_MEMORY_BYTES 100'000'000

namespace Eclipse
{
	namespace Editor {
		class HierarchyWindow;
		class InspectorWindow;
		class EditorActions;
	}

	typedef unsigned ComponentIndex;

	class GameObject;
	class Component;
	class ComponentManager
	{
		friend class Editor::EditorActions;
		friend class Editor::HierarchyWindow;
		friend class Editor::InspectorWindow;
		friend class SceneLoader;

	public:
		ComponentManager() = default;
		~ComponentManager() = default;

		static void Init();

		static void OnLoadScene();

		static void AwakeStartComponents();

		static void AwakeComponents();
		static void StartComponents();

		static void EditorUpdateComponents();

		static void EarlyUpdateComponents();
		static void UpdateComponents();
		static void LateUpdateComponents();
		static void RenderComponents();

		static void SortComponents();

		static void BeginCollisions(GameObjectID aGOID);
		static void EndCollisions(GameObjectID aGOID);

		template <typename T>
		static T* GetComponent(GameObjectID aGOID);

		template <typename T>
		static T* AddComponent(GameObjectID aGOID);

		template <typename T>
		static void RemoveComponent(GameObjectID aGOID);

		template <typename T>
		static T* AddComponentWithID(GameObjectID aGOID, unsigned aComponentID);


		static Eclipse::Component* AddComponent(GameObjectID aGOID, Eclipse::Component* (__cdecl* createFunc)(unsigned char* address), size_t size);

		static Eclipse::Component* AddComponentWithID(GameObjectID aGOID, unsigned aComponentID, Eclipse::Component* (__cdecl* createFunc)(unsigned char* address), size_t size);



		template <typename T>
		static unsigned GetComponentID();

		static const std::vector<Component*>& GetAllComponents();

		static std::vector<Component*> GetComponents(GameObjectID aGOID);


		static bool HasGameObject(GameObjectID aGOID);

		static void Destroy(GameObjectID aGOID);

		static GameObject* CreateGameObject();
		static GameObject* CreateGameObjectNoTransform();
		static GameObject* CreateGameObjectNoTransformWithID(GameObjectID aId);

		static void Clear();

	private:
		static inline size_t myComponentMemoryTracker = 0;
		static inline uint8_t* myComponentData;

		static inline std::vector<Component*> myComponents;
		static inline unsigned myNextGameobjectID = 1;

		static inline std::vector<Component*> myComponentsToStart;

		// Gameobject to components
		static inline std::unordered_map<GameObjectID, GameObject*> myEntityIdToEntity;
		static inline std::unordered_map<GameObjectID, std::unordered_map<unsigned, ComponentIndex>> myEntityIDToVectorOfComponentIDs;
	};
}

#include "ComponentManager.inl"