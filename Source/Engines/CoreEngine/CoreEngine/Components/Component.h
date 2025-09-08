#pragma once

#include "Interfaces/Serializable.h"
#include <string>

#include "defines.h"

/*#define BASE_COMPONENT(type) BASE_COMPONENT(type, 0)

#define BASE_COMPONENT(type, updatePriority)                                            \
inline type() : Component(stringify(type), updatePriority) {}                           \
inline ~type() = default;      */

namespace ENGINE_NAMESPACE::Editor
{
	class InspectorWindow;
}

#define COMPONENT_FRIEND_CLASS         \
friend class Editor::InspectorWindow;  \
friend class ComponentManager;         \
friend class SceneLoader;              \


#define DERIVED_COMPONENT(type, derivedType, updatePriority)				\
COMPONENT_FRIEND_CLASS														\
public:																		\
    inline type() : derivedType(updatePriority) {}							\
virtual ~type() = default;													\
protected:																	\
virtual const char* GetComponentName() override { return stringify(type); }	\
private:


#define BASE_BASE_COMPONENT(type)											\
COMPONENT_FRIEND_CLASS														\
public:																		\
inline type(unsigned updatePriority) : Component(updatePriority) {}			\
virtual ~type() = default;													\
private:


#define BASE_COMPONENT(type, updatePriority)								\
COMPONENT_FRIEND_CLASS														\
public:																		\
inline type() : Component(updatePriority) {}								\
virtual ~type() = default;													\
protected:																	\
virtual const char* GetComponentName() override { return stringify(type); }	\
private:
        



namespace ENGINE_NAMESPACE
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
		virtual void DrawInspector() {};
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