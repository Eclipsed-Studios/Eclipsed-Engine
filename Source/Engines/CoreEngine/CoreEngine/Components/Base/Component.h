#pragma once

#include "Interfaces/Serializable.h"
#include <string>

#include "defines.h"
#include "Editor/ComponentRegistry.h"

#include "Editor/Reflection/Reflection.h"

namespace Eclipse::Editor
{
	class InspectorWindow;
}

namespace Eclipse
{
	typedef unsigned RegisteredTypeIndex;
	typedef unsigned GameObject;

	class Component : public ISerializable
	{
		friend class Editor::InspectorWindow;

		friend class ComponentManager;
		friend class SceneLoader;

	public:
		Component() = default;
		Component(unsigned updatePriority);
		virtual ~Component() = default;

		void SetComponentID() { myComponentID = ++nextComponentID; }

	public:
		virtual void Awake() {}
		virtual void Start() {}

		virtual void EarlyUpdate() {}
		virtual void Update() {}
		virtual void LateUpdate() {}

		virtual void OnCollisionEnter() {}
		virtual void OnCollisionExit() {}

		virtual void OnDrawGizmos() {}

	protected:
		virtual void DrawInspector() { Reflection::DrawInspector(this); };
		virtual const char* GetComponentName() { return "Component"; }

	public:
		virtual rapidjson::Value Save(rapidjson::Document::AllocatorType& allocator) const override;
		virtual void Load(const rapidjson::Value& aValue) override;

	public:
		GameObject gameObject;

	protected:
		// Higher number higher priority
		unsigned myUpdateStartPriority = 0;

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