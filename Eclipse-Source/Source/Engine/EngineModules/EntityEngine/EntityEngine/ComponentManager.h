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

		static void BeginCollisions(unsigned aGOID);
		static void EndCollisions(unsigned aGOID);

		template <typename T>
		static T* GetComponent(unsigned aGOID);

		template <typename T>
		static T* AddComponent(unsigned aGOID);

		template <typename T>
		static void RemoveComponent(unsigned aGOID);

		template <typename T>
		static T* AddComponentWithID(unsigned aGOID, unsigned aComponentID);


		static Eclipse::Component* AddComponent(unsigned aGOID, Eclipse::Component* (__cdecl* createFunc)(unsigned char* address), size_t size);

		static Eclipse::Component* AddComponentWithID(unsigned aGOID, unsigned aComponentID, Eclipse::Component* (__cdecl* createFunc)(unsigned char* address), size_t size);



		template <typename T>
		static unsigned GetComponentID();

		static const std::vector<Component*>& GetAllComponents();

		static std::vector<Component*> GetComponents(unsigned aGOID);


		static bool HasGameObject(unsigned aGOID);

		static void Destroy(unsigned aGOID);

		static GameObject* CreateGameObject();
		static GameObject* CreateGameObjectNoTransform();
		static GameObject* CreateGameObjectNoTransformWithID(unsigned aId);

		static void Clear();

	private:
		static inline size_t myComponentMemoryTracker = 0;
		static inline uint8_t* myComponentData;

		static inline std::vector<Component*> myComponents;
		static inline unsigned myNextGameobjectID = 1;

		static inline std::vector<Component*> myComponentsToStart;

		// Gameobject to components
		static inline std::unordered_map<unsigned, GameObject*> myEntityIdToEntity;
		static inline std::unordered_map<unsigned, std::unordered_map<unsigned, ComponentIndex>> myEntityIDToVectorOfComponentIDs;
	};
}

#include "ComponentManager.inl"