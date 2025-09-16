#ifndef REFLECTION_MACROS_H
#define REFLECTION_MACROS_H

#include "SerializedEnum.hpp"
#include "Reflection.h"
#include "SerializedVariable.h"

#define MAKE_SERIALIZABLE static constexpr bool serializable = true

#define SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, DefaultValue}
#define SERIALIZED_FIELD(Type, Name, DefaultValue) SERIALIZED_FIELD_DEFAULT(Type, Name, {})

#endif