#pragma once

#include "Editor/ComponentRegistry.h"
#include "ECS/ComponentManager.h"

#include "defines.h"
#include "Component.h"

#define BASE_MACRO_NAME COMPONENT_BASE
#include "MacroOverloadSelector.h"

#define COMPONENT_FRIEND_CLASS         \
friend class Editor::InspectorWindow;  \
friend class ComponentManager;         \
friend class SceneLoader;              \





#define COMPONENT_BASE_1(type)											\
COMPONENT_FRIEND_CLASS														\
public:																		\
inline type(unsigned updatePriority) : Component(updatePriority) {}			\
virtual ~type() = default;													\
private:

#define REGISTER_COMPONENT_CALLBACK(type) [](int id){ ComponentManager::AddComponent<type>(id); }



#define COMPONENT_BASE_2(type, updatePriority)														\
COMPONENT_FRIEND_CLASS																				\
public:																								\
inline type() : Component(updatePriority) {}														\
virtual ~type() = default;																			\
protected:																							\
virtual const char* GetComponentName() override { return stringify(type); }							\
private:																							\
struct AutoRegister {																				\
	AutoRegister() {																				\
		using namespace ENGINE_NAMESPACE::Editor;													\
		ComponentRegistry::RegisterComponent(stringify(type), REGISTER_COMPONENT_CALLBACK(type));	\
	}																								\
};																									\
AutoRegister _register = {};


#define COMPONENT_BASE_3(type, derivedType, updatePriority)				\
COMPONENT_FRIEND_CLASS														\
public:																		\
    inline type() : derivedType(updatePriority) {}							\
virtual ~type() = default;													\
protected:																	\
virtual const char* GetComponentName() override { return stringify(type); }	\
private: