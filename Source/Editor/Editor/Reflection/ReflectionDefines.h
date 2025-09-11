#pragma once

#include "Editor/Reflection/ReflectedVariable.h"

namespace ENGINE_NAMESPACE {
    template<typename T>
    class ReflectedVariable;
}

#define ReflectedVar_Default(type, name, defaultValue) \
    ENGINE_NAMESPACE::ReflectedVariable<type> name{#name, #type, this, defaultValue}

#define ReflectedVar(type, name) \
    ReflectedVar_Default(type, name, {})

#define RVar(name) int name = 0