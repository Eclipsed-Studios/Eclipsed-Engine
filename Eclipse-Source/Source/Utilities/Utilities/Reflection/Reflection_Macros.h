#ifndef REFLECTION_MACROS_H
#define REFLECTION_MACROS_H

#include "SerializedEnum.hpp"
#include "Reflection.h"
#include "SerializedVariable.h"

// Will draw a custom inspector for this component.
#define SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue}

// Will draw a custom inspector for this component.
#define SERIALIZED_FIELD(Type, Name) Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true}


// Will draw custom inspector for this component with min and max values.
#define SERIALIZED_FIELD_DEFAULT_MIN_MAX(Type, Name, DefaultValue, Min, Max) Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue, Min, Max}

// Will draw custom inspector for this component with min and max values.
#define SERIALIZED_FIELD_MIN_MAX(Type, Name, Min, Max) Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, Min, Max}


// Will not draw an inspector and just be serializable.
#define PRIVATE_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false, DefaultValue}

// Will not draw an inspector and just be serializable.
#define PRIVATE_SERIALIZED_FIELD(Type, Name) Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false}



#endif