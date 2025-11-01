#pragma once

//#include "BaseComponent.h"
#include "Utilities/Interfaces/Serializable.h"
#include <string>

#include "Utilities/Reflection/Registry/ComponentRegistry.h"

#include "Utilities/Reflection/Reflection.h"
#include "Utilities/Reflection/Reflection_Macros.h"

namespace Eclipse
{
	namespace Editor
	{
		class SceneWindow;
	}
	namespace Editor
	{
		class InspectorWindow;
	}
	namespace Editor
	{
		class HierarchyWindow;
	}
	namespace Reflection
	{
		class ReflectionManager;
	}
}

namespace Eclipse
{
	typedef unsigned RegisteredTypeIndex;

	class GameObject;
	class ComponentManager;
	class Component
	{
		friend class Editor::HierarchyWindow;
		friend class Editor::SceneWindow;
		friend class Editor::InspectorWindow;
		friend class Reflection::ReflectionManager;

		friend class ComponentManager;
		friend class SceneLoader;

	public:
		Component() = default;
		virtual ~Component() = default;

		void SetComponentID() { myInstanceComponentID = ++nextComponentID; }
		void SetComponentID(unsigned compID)
		{
			myInstanceComponentID = compID;

			if (nextComponentID <= compID)
			{
				nextComponentID = compID++;
			}
			else
			{
				nextComponentID++;
			}
		}

		virtual unsigned GetUpdatePriority() const = 0;

	public:
		virtual void OnSceneLoaded() {}

		virtual void OnComponentAdded() {}
		virtual void OnDestroy() {}

		virtual void Awake() {}
		virtual void Start() {}

		virtual void EditorUpdate() {}

		virtual void EarlyUpdate() {}
		virtual void Update() {}
		virtual void LateUpdate() {}

		virtual void Render() {}

		virtual void OnCollisionEnter() {}
		virtual void OnCollisionExit() {}

		virtual void OnDrawGizmos() {}

		virtual const char* GetComponentName() { return "Component"; }

	protected:
#ifdef ECLIPSED_EDITOR
		void UpdateInspector() { Reflection::ReflectionManager::DrawInspector(this, GetComponentName()); DrawInspector(); }
#endif

		virtual void DrawInspector() {}


	public:
		GameObject* gameObject;

	protected:
		unsigned myInstanceComponentID = 0;
		unsigned myComponentIndex = 0;

	private:
		RegisteredTypeIndex myComponentComponentID;
		static inline unsigned nextComponentID = 0;

	protected:
		// IF DEF EDITOR
		bool myInspectorWasDrawn = false;
	};
}