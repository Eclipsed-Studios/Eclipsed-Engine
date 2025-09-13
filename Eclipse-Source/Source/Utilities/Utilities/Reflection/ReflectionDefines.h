#pragma once

#include "Reflection/ReflectedVariable.h"

namespace Eclipse {
    template<typename T>
    class ReflectedVariable;
}

#define ReflectedVar_Default(type, name, defaultValue) \
    Eclipse::ReflectedVariable<type> name{#name, #type, this->myComponentID, this, defaultValue}

#define ReflectedVar(type, name) \
    ReflectedVar_Default(type, name, {})

#define RVar(name) int name = 0