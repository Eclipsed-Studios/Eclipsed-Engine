#pragma once

#include <string>
#include "Types.h"

namespace Eclipse
{
	namespace Editor
	{
		class SceneWindow;
		class InspectorWindow;
		class HierarchyWindow;
		class EditorActions;
	}
	namespace Reflection
	{
		class ReflectionManager;
		class AbstractSerializedVariable;
	}
}

namespace Eclipse
{
	class GameObject;
	class ComponentManager;
	class Component
	{
		friend class ReplicatedVariable;
		friend class Editor::EditorActions;
		friend class Editor::HierarchyWindow;
		friend class Editor::SceneWindow;
		friend class Editor::InspectorWindow;
		friend class Reflection::ReflectionManager;
		friend class Reflection::AbstractSerializedVariable;

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

		// If defined then the default inspector will be overwritten.
		virtual void OnDrawInspector() {}

		virtual void Render() {}

		virtual void OnCollisionEnter() {}
		virtual void OnCollisionExit() {}

		virtual void OnDrawGizmos() {}

		virtual const char* GetComponentName() { return "Component"; }


	protected:
#ifdef ECLIPSED_EDITOR
		virtual void UpdateInspector() {}
#endif
//#ifdef ECLIPSED_EDITOR
//		void UpdateInspector() { Reflection::ReflectionManager::DrawInspector(this, GetComponentName()); }
//#endif


	public:
		//SERIALIZED_FIELD_DEFAULT(bool, IsReplicated, false);

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
		virtual bool HasDrawInspector() const { return false; }
		virtual bool DrawDefaultInspector() const { return true; }
	};
}