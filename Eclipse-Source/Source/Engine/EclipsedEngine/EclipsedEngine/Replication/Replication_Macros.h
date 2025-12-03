#pragma once

// #include "SerializedEnum.hpp"
// #include "Reflection.h"
// #include "SerializedVariable.h"

#include "Replication.h"

// #define REPLICATED_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
// Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue}; \
// Eclipse::Replication::ReplicatedVariableList.emplace(#Name, this)

// #define REPLICATED_SERIALIZED_FIELD(Type, Name) \
// Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true}; \
// Eclipse::Replication::ReplicatedVariableList.emplace(#Name, this)

// #define REPLICATED_SERIALIZED_FIELD_DEFAULT_MIN_MAX(Type, Name, DefaultValue, Min, Max) \
// Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue, Min, Max}; \
// Eclipse::Replication::ReplicatedVariableList.emplace(#Name, this)

// #define REPLICATED_SERIALIZED_FIELD_MIN_MAX(Type, Name, Min, Max) \
// Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, Min, Max}; \
// Eclipse::Replication::ReplicatedVariableList.emplace(#Name, this)

// #define REPLICATED_PRIVATE_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
// Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false, DefaultValue}; \
// Eclipse::Replication::ReplicatedVariableList.emplace(#Name, this)

// #define REPLICATED_PRIVATE_SERIALIZED_FIELD(Type, Name) \
// Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false};  \
// Eclipse::Replication::ReplicatedVariableList.emplace(#Name, this)


#define REPLICATED_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
Eclipse::Replication::ReplicatedVariableList.emplace(#Name, this)

#define REPLICATED_SERIALIZED_FIELD(Type, Name) \
Eclipse::Replication::ReplicatedVariableList.emplace(#Name, this)

#define REPLICATED_SERIALIZED_FIELD_DEFAULT_MIN_MAX(Type, Name, DefaultValue, Min, Max) \
Eclipse::Replication::ReplicatedVariableList.emplace(#Name, this)

#define REPLICATED_SERIALIZED_FIELD_MIN_MAX(Type, Name, Min, Max) \
Eclipse::Replication::ReplicatedVariableList.emplace(#Name, this)

#define REPLICATED_PRIVATE_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
Eclipse::Replication::ReplicatedVariableList.emplace(#Name, this)

#define REPLICATED_PRIVATE_SERIALIZED_FIELD(Type, Name) \
Eclipse::Replication::ReplicatedVariableList.emplace(#Name, this)