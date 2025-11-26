#pragma once

#include "Utilities/Reflection/SerializedVariable.h"
#include "ReplicatedVariable.h"

//#define REPLICATE()

#define REPL(Name, Auto, ReplicatedIndex) Eclipse::Replication::ReplicatedVariable Repl##Name{#Name, this, Auto, ReplicatedIndex}

#define REPLICATED_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue}; \
REPL(Name, true, Name.ReplicatedVariableIndex)

#define REPLICATED_SERIALIZED_FIELD(Type, Name) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true}; \
REPL(Name, true, Name.ReplicatedVariableIndex)

#define REPLICATED_SERIALIZED_FIELD_DEFAULT_MIN_MAX(Type, Name, DefaultValue, Min, Max) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue, Min, Max}; \
REPL(Name, true, Name.ReplicatedVariableIndex)

#define REPLICATED_SERIALIZED_FIELD_MIN_MAX(Type, Name, Min, Max) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, Min, Max}; \
REPL(Name, true, Name.ReplicatedVariableIndex)

#define REPLICATED_PRIVATE_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false, DefaultValue}; \
REPL(Name, true, Name.ReplicatedVariableIndex)

#define REPLICATED_PRIVATE_SERIALIZED_FIELD(Type, Name) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false};  \
REPL(Name, true, Name.ReplicatedVariableIndex)




#define MANUAL_REPLICATED_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue}; \
REPL(Name, false, Name.ReplicatedVariableIndex)

#define MANUAL_REPLICATED_SERIALIZED_FIELD(Type, Name) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true}; \
REPL(Name, false, Name.ReplicatedVariableIndex)

#define MANUAL_REPLICATED_SERIALIZED_FIELD_DEFAULT_MIN_MAX(Type, Name, DefaultValue, Min, Max) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue, Min, Max}; \
REPL(Name, false, Name.ReplicatedVariableIndex)

#define MANUAL_REPLICATED_SERIALIZED_FIELD_MIN_MAX(Type, Name, Min, Max) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, Min, Max}; \
REPL(Name, false, Name.ReplicatedVariableIndex)

#define MANUAL_REPLICATED_PRIVATE_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false, DefaultValue}; \
REPL(Name, false, Name.ReplicatedVariableIndex)

#define MANUAL_REPLICATED_PRIVATE_SERIALIZED_FIELD(Type, Name) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false};  \
REPL(Name, false, Name.ReplicatedVariableIndex)