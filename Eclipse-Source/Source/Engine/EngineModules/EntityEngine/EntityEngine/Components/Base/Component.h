#pragma once

//#include "BaseComponent.h"
#include "Utilities/Interfaces/Serializable.h"
#include <string>

#include "Utilities/Reflection/Registry/ComponentRegistry.h"

#include "Utilities/Reflection/Reflection.h"
#include "Utilities/Reflection/Reflection_Macros.h"

#include "Utilities/Math/Random.h"

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
	}
}

namespace Eclipse
{
	typedef unsigned RegisteredTypeIndex;


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

		friend class ComponentManager;
		friend class SceneLoader;

	public:
		Component() = default;
		virtual ~Component() = default;

		static unsigned GetNextComponentID() 
		{
			return Random::Rand<unsigned>();
		}

		void SetComponentID() 
		{ 
			myInstanceComponentID = GetNextComponentID(); 
		}

		void SetComponentID(unsigned compID)
		{
			myInstanceComponentID = compID;
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

		bool IsOwner() { return myIsOwner; }
		void SetIsOwner(bool anIsOwner) { myIsOwner = anIsOwner; }

	protected:
#ifdef ECLIPSED_EDITOR
		void UpdateInspector() { 
			std::stringstream stream;
			stream << "ID: " << myInstanceComponentID;
			ImGui::Text(stream.str().c_str());
			Reflection::ReflectionManager::DrawInspector(this, GetComponentName()); }
#endif


	public:
		SERIALIZED_FIELD_DEFAULT(bool, IsReplicated, true);

		GameObject* gameObject;

		unsigned myInstanceComponentID = 0;
	protected:
		unsigned myComponentIndex = 0;

	private:
		RegisteredTypeIndex myComponentComponentID;
		static inline unsigned nextComponentID = 0;

	protected:
		// IF DEF EDITOR
		bool myInspectorWasDrawn = false;

		bool myIsOwner = true;
	};
}