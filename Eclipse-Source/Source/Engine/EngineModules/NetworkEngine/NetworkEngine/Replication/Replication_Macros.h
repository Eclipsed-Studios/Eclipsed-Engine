#pragma once

#include "Utilities/Reflection/SerializedVariable.h"
#include "ReplicatedVariable.h"
#include "ReplicationManager.h"

// Use this as a standalone Macro with the serilized variable as arg
#define REPLICATE(Variable) Replication::ReplicationManager::ReplicatedVariableList.at(Variable.ReplicatedVariableIndex)->ReplicateThis(Variable.ReplicatedVariableIndex)

#define REPLICATEHELPERMACRONOTUSE(Name, Auto, ReplicatedIndex, FunctionPtr) Eclipse::Replication::ReplicatedVariable Repl##Name{#Name, this, Auto, ReplicatedIndex, FunctionPtr}
#define ONREPPEDFUNCTIONDEF(Name) void Name##_OnRep()

#define REPLICATED_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue}; \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, true, Name.ReplicatedVariableIndex, &Name##_OnRep)

#define REPLICATED_SERIALIZED_FIELD(Type, Name) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true}; \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, true, Name.ReplicatedVariableIndex, &#Name##_OnRep)

#define REPLICATED_SERIALIZED_FIELD_DEFAULT_MIN_MAX(Type, Name, DefaultValue, Min, Max) \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, true, Name.ReplicatedVariableIndex, &Name##_OnRep)

#define REPLICATED_SERIALIZED_FIELD_MIN_MAX(Type, Name, Min, Max) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, Min, Max}; \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, true, Name.ReplicatedVariableIndex, &Name##_OnRep)

#define REPLICATED_PRIVATE_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false, DefaultValue}; \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, true, Name.ReplicatedVariableIndex, &Name##_OnRep)

#define REPLICATED_PRIVATE_SERIALIZED_FIELD(Type, Name) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false};  \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, true, Name.ReplicatedVariableIndex, &Name##_OnRep)




#define MANUAL_REPLICATED_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue}; \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, false, Name.ReplicatedVariableIndex, &Name##_OnRep)

#define MANUAL_REPLICATED_SERIALIZED_FIELD(Type, Name) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true}; \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, false, Name.ReplicatedVariableIndex, &Name##_OnRep)

#define MANUAL_REPLICATED_SERIALIZED_FIELD_DEFAULT_MIN_MAX(Type, Name, DefaultValue, Min, Max) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue, Min, Max}; \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, false, Name.ReplicatedVariableIndex, &Name##_OnRep)

#define MANUAL_REPLICATED_SERIALIZED_FIELD_MIN_MAX(Type, Name, Min, Max) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, Min, Max}; \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, false, Name.ReplicatedVariableIndex, &Name##_OnRep)

#define MANUAL_REPLICATED_PRIVATE_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false, DefaultValue}; \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, false, Name.ReplicatedVariableIndex, &Name##_OnRep)

#define MANUAL_REPLICATED_PRIVATE_SERIALIZED_FIELD(Type, Name) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false};  \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, false, Name.ReplicatedVariableIndex, &Name##_OnRep)