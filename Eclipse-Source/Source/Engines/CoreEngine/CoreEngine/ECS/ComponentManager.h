#pragma once

#include "Components/Base/Component.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <typeindex>
#include <assert.h>

#define GetComp(Type, GOID)\
ComponentManager::GetComponent<##Type>(GOID)

#define MAX_COMPONENT_MEMORY_BYTES 100'000

namespace Eclipse
{
	namespace Editor {
		class HierarchyWindow;
		class InspectorWindow;
	}

	typedef unsigned ComponentIndex;

	class GameObject;
	class ComponentManager
	{
		friend class Editor::HierarchyWindow;
		friend class Editor::InspectorWindow;
		friend class SceneLoader;

	public:
		ComponentManager() = default;
		~ComponentManager() = default;

		static void Init();

		static void AwakeStartComponents();

		static void AwakeComponents();
		static void StartComponents();

		static void EarlyUpdateComponents();
		static void UpdateComponents();
		static void LateUpdateComponents();

		static void SortSHit();

		static void BeginCollisions(GameObjectID aGOID);
		static void EndCollisions(GameObjectID aGOID);

		template <typename T>
		static T* GetComponent(GameObjectID aGOID);

		template <typename T>
		static T* AddComponent(GameObjectID aGOID);

		template <typename T>
		static T* AddComponentWithID(GameObjectID aGOID, unsigned aComponentID);

		template <typename T>
		static void RemoveComponent(GameObjectID aGOID);

		static const std::vector<Component*>& GetComponents();

		static GameObject* CreateGameObject();
		static GameObject* CreateGameObjectNoTransform();

	private:
		static inline size_t myComponentMemoryTracker = 0;
		static inline uint8_t* myComponentData;

		static inline std::vector<Component*> myComponents;
		static inline unsigned myNextGameobjectID = 1;

		static inline std::vector<Component*> myComponentsToStart;

		// Gameobject to components
		static inline std::unordered_map<GameObjectID, GameObject*> myEntityIdToEntity;
		static inline std::unordered_map<GameObjectID, std::unordered_map<RegisteredTypeIndex, ComponentIndex>> myEntityIDToVectorOfComponentIDs;
	};
}

#include "ComponentManager.inl"