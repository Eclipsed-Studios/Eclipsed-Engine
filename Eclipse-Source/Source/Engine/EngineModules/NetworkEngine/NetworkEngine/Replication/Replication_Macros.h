#pragma once

#include "Utilities/Reflection/SerializedVariable.h"
#include "ReplicatedVariable.h"
#include "ReplicationManager.h"

// Use this as a standalone Macro with the serilized variable as arg
#define REPLICATE(Variable) Replication::ReplicationManager::ReplicatedVariableList.at(Variable.ReplicatedVariableIndex)->ReplicateThis(Variable.ReplicatedVariableIndex)

#define REPLICATEHELPERMACRONOTUSE(Name, Auto, ReplicatedIndex) Eclipse::Replication::ReplicatedVariable Repl##Name{#Name, this, Auto, ReplicatedIndex}

#define REPLICATED_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue}; \
REPLICATEHELPERMACRONOTUSE(Name, true, Name.ReplicatedVariableIndex)

#define REPLICATED_SERIALIZED_FIELD(Type, Name) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true}; \
REPLICATEHELPERMACRONOTUSE(Name, true, Name.ReplicatedVariableIndex)

#define REPLICATED_SERIALIZED_FIELD_DEFAULT_MIN_MAX(Type, Name, DefaultValue, Min, Max) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue, Min, Max}; \
REPLICATEHELPERMACRONOTUSE(Name, true, Name.ReplicatedVariableIndex)

#define REPLICATED_SERIALIZED_FIELD_MIN_MAX(Type, Name, Min, Max) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, Min, Max}; \
REPLICATEHELPERMACRONOTUSE(Name, true, Name.ReplicatedVariableIndex)

#define REPLICATED_PRIVATE_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false, DefaultValue}; \
REPLICATEHELPERMACRONOTUSE(Name, true, Name.ReplicatedVariableIndex)

#define REPLICATED_PRIVATE_SERIALIZED_FIELD(Type, Name) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false};  \
REPLICATEHELPERMACRONOTUSE(Name, true, Name.ReplicatedVariableIndex)




#define MANUAL_REPLICATED_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue}; \
REPLICATEHELPERMACRONOTUSE(Name, false, Name.ReplicatedVariableIndex)

#define MANUAL_REPLICATED_SERIALIZED_FIELD(Type, Name) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true}; \
REPLICATEHELPERMACRONOTUSE(Name, false, Name.ReplicatedVariableIndex)

#define MANUAL_REPLICATED_SERIALIZED_FIELD_DEFAULT_MIN_MAX(Type, Name, DefaultValue, Min, Max) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue, Min, Max}; \
REPLICATEHELPERMACRONOTUSE(Name, false, Name.ReplicatedVariableIndex)

#define MANUAL_REPLICATED_SERIALIZED_FIELD_MIN_MAX(Type, Name, Min, Max) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, Min, Max}; \
REPLICATEHELPERMACRONOTUSE(Name, false, Name.ReplicatedVariableIndex)

#define MANUAL_REPLICATED_PRIVATE_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false, DefaultValue}; \
REPLICATEHELPERMACRONOTUSE(Name, false, Name.ReplicatedVariableIndex)

#define MANUAL_REPLICATED_PRIVATE_SERIALIZED_FIELD(Type, Name) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false};  \
REPLICATEHELPERMACRONOTUSE(Name, false, Name.ReplicatedVariableIndex)