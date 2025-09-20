#ifndef REFLECTION_MACROS_H
#define REFLECTION_MACROS_H

#include "SerializedEnum.hpp"
#include "Reflection.h"
#include "SerializedVariable.h"

#define SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, DefaultValue}
#define SERIALIZED_FIELD(Type, Name) SERIALIZED_FIELD_DEFAULT(Type, Name, {})

#endif