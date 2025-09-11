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

	typedef unsigned GameObject;
	typedef unsigned ComponentIndex;

	struct GameObjectData
	{
		std::string name = "New Gameobject";
	};

	class ComponentManager
	{
		friend class Editor::HierarchyWindow;
		friend class Editor::InspectorWindow;

	public:
		ComponentManager() = default;
		~ComponentManager() = default;

		static void Init();

		static void AwakeComponents();
		static void StartComponents();

		static void EarlyUpdateComponents();
		static void UpdateComponents();
		static void LateUpdateComponents();

		static void BeginCollisions(GameObject aGOID);
		static void EndCollisions(GameObject aGOID);

		template <typename T>
		static T* GetComponent(GameObject aGOID);

		template <typename T>
		static T* AddComponent(GameObject aGOID);

		template <typename T>
		static void RemoveComponent(GameObject aGOID);

		static const std::vector<Component*>& GetComponents();

	private:
		static inline size_t myComponentMemoryTracker = 0;
		static inline char* myComponentData;

		static inline std::vector<Component*> myComponents;

		// Gameobject to components
		static inline std::unordered_map<GameObject, GameObjectData> myEntityIdToEntityData;
		static inline std::unordered_map<GameObject, std::unordered_map<RegisteredTypeIndex, ComponentIndex>> myEntityIDToVectorOfComponentIDs;
	};
}

#include "ComponentManager.inl"