#pragma once

#include "Utilities/Reflection/SerializedVariable.h"
#include "ReplicatedVariable.h"

#define REPL(Name, Auto) Eclipse::Replication::ReplicatedVariable Replicated##Name{#Name, this, Auto}

#define REPLICATED_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue}; \
REPL(Name, true)

#define REPLICATED_SERIALIZED_FIELD(Type, Name) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true}; \
REPL(Name, true)

#define REPLICATED_SERIALIZED_FIELD_DEFAULT_MIN_MAX(Type, Name, DefaultValue, Min, Max) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue, Min, Max}; \
REPL(Name, true)

#define REPLICATED_SERIALIZED_FIELD_MIN_MAX(Type, Name, Min, Max) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, Min, Max}; \
REPL(Name, true)

#define REPLICATED_PRIVATE_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false, DefaultValue}; \
REPL(Name, true)

#define REPLICATED_PRIVATE_SERIALIZED_FIELD(Type, Name) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false};  \
REPL(Name, true)




#define MANUAL_REPLICATED_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue}; \
REPL(Name, false)

#define MANUAL_REPLICATED_SERIALIZED_FIELD(Type, Name) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true}; \
REPL(Name, false)

#define MANUAL_REPLICATED_SERIALIZED_FIELD_DEFAULT_MIN_MAX(Type, Name, DefaultValue, Min, Max) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue, Min, Max}; \
REPL(Name, false)

#define MANUAL_REPLICATED_SERIALIZED_FIELD_MIN_MAX(Type, Name, Min, Max) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, Min, Max}; \
REPL(Name, false)

#define MANUAL_REPLICATED_PRIVATE_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false, DefaultValue}; \
REPL(Name, false)

#define MANUAL_REPLICATED_PRIVATE_SERIALIZED_FIELD(Type, Name) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false};  \
REPL(Name, false)