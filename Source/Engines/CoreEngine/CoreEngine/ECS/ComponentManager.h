#pragma once

#include "Components/Component.h"

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <assert.h>

#define GetComp(Type, GOID)\
ComponentManager::GetComponent<##Type>(GOID)

#define MAX_COMPONENT_MEMORY_BYTES 100'000

namespace ENGINE_NAMESPACE
{
	typedef unsigned GameObject;

	class ComponentManager
	{
	public:
		ComponentManager() = default;
		~ComponentManager() = default;

		static void Init();

		static void AwakeComponents();
		static void StartComponents();

		static void EarlyUpdateComponents();
		static void UpdateComponents();
		static void LateUpdateComponents();

		template <typename T>
		static T* GetComponent(GameObject aGOID);

		template <typename T>
		static T* AddComponent(GameObject aGOID);

		template <typename T>
		static void RemoveComponent(GameObject aGOID);

	private:
		static inline size_t myComponentMemoryTracker = 0;
		static inline char* myComponentData;

		static inline std::vector<Component*> myComponents;

		// Gameobject to components
		static inline  std::unordered_map<GameObject, std::unordered_map<std::type_index, unsigned>> myEntityIDToVectorOfComponentIDs;
	};
}

#include "ComponentManager.inl"