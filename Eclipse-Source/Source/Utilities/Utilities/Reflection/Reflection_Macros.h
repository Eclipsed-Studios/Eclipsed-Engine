#ifndef REFLECTION_MACROS_H
#define REFLECTION_MACROS_H

#include "SerializedEnum.hpp"
#include "Reflection.h"
#include "SerializedVariable.h"

#define SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue}
#define SERIALIZED_FIELD(Type, Name) Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true}


#define SERIALIZED_FIELD_DEFAULT_MIN_MAX(Type, Name, DefaultValue, Min, Max) Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue, Min, Max}
#define SERIALIZED_FIELD_MIN_MAX(Type, Name, Min, Max) Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, Min, Max}

#define PRIVATE_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false, DefaultValue}
#define PRIVATE_SERIALIZED_FIELD(Type, Name) Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false}



#endif