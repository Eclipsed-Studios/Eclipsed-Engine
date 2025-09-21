#ifndef _BASECOMPONENT
#define _BASECOMPONENT

#include "Reflection/Registry/ComponentRegistry.h"

#include "ECS/ComponentManager.h"

#include "defines.h"
#include "Component.h"

#pragma warning (push)
#pragma warning (disable:4005)
#define BASE_MACRO_NAME COMPONENT_BASE
#pragma warning(pop)

#include "MacroOverloadSelector.h"

#define COMPONENT_FRIEND_CLASS         \
friend class Editor::InspectorWindow;  \
friend class ComponentManager;         \
friend class SceneLoader;              

#define COMPONENT_BASE_1(type)												\
COMPONENT_FRIEND_CLASS														\
public:																		\
inline type() = default;													\
virtual ~type() = default;													\
private:


#define REGISTER_COMPONENT_CALLBACK(type) [](unsigned gameObjId, unsigned compID){ return ComponentManager::AddComponentWithID<type>(gameObjId, compID); }



#define COMPONENT_BASE_2(type, updatePriority)														\
COMPONENT_FRIEND_CLASS																				\
public:																								\
virtual unsigned GetUpdatePriority() const override {return updatePriority;}						\
inline type() = default;																			\
virtual ~type() = default;																			\
protected:																							\
virtual const char* GetComponentName() override { return stringify(type); }							\
private:																							\
struct AutoRegister {																				\
	AutoRegister() {																				\
		using namespace Eclipse;																	\
		ComponentRegistry::Register(stringify(type), REGISTER_COMPONENT_CALLBACK(type));			\
	}																								\
};																									\
public: \
static inline AutoRegister _register = {};




#define COMPONENT_BASE_3(type, derivedType, updatePriority)				\
COMPONENT_FRIEND_CLASS														\
public:																		\
    inline type() = default;										\
virtual ~type() = default;													\
protected:																	\
virtual const char* GetComponentName() override { return stringify(type); }	\
private:


#define FORCELINK(Class)												\
	namespace {															\
		static auto& forceLink = Eclipse::Class::_register;				\
	}
#endif