#pragma once

#include "BaseComponent.h"
#include "Interfaces/Serializable.h"
#include <string>

#include "defines.h"
#include "Reflection/Registry/ComponentRegistry.h"

#include "Reflection/Reflection.h"
#include "Reflection/Reflection_Macros.h"
#include "GameObject.h"

namespace Eclipse
{
	namespace Editor
	{
		class InspectorWindow;
	}
	namespace Reflection
	{
		class ReflectionManager;
	}
}

namespace Eclipse
{
	typedef unsigned RegisteredTypeIndex;

	class Component
	{
		friend class Editor::InspectorWindow;
		friend class Reflection::ReflectionManager;

		friend class ComponentManager;
		friend class SceneLoader;

	public:
		Component() = default;
		virtual ~Component() = default;

		void SetComponentID() { myComponentID = ++nextComponentID; }
		void SetComponentID(unsigned compID)
		{
			myComponentID = compID;

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

	protected:
		virtual void DrawInspector() { Reflection::ReflectionManager::DrawInspector(this); };
		virtual const char* GetComponentName() { return "Component"; }

	public:
		GameObject* gameObject;

	protected:
		unsigned myComponentID = 0;
		unsigned myComponentIndex = 0;

	private:
		RegisteredTypeIndex myUniqueComponentID;
		static inline unsigned nextComponentID = 0;

	protected:
		// IFDEF EDITOR
		bool myInspectorWasDrawn = false;
	};
}