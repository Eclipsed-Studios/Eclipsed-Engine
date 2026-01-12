#pragma once

#include "EclipsedEngine/Reflection/SerializedVariable.h"
#include "ReplicatedVariable.h"
#include "ReplicationManager.h"

// Use this as a standalone Macro with the serilized variable as arg
#define REPLICATE(Variable) Replication::ReplicationManager::RealReplicatedVariableList.at(myInstanceComponentID)[sprite.ReplicatedVariableIndex]->ReplicateThis(sprite.ReplicatedVariableIndex, false);
#define REPLICATEGARANTIED(Variable) Replication::ReplicationManager::RealReplicatedVariableList.at(myInstanceComponentID)[sprite.ReplicatedVariableIndex]->ReplicateThis(sprite.ReplicatedVariableIndex, true);

#define REPLICATEHELPERMACRONOTUSE(Name, Auto, ReplicatedIndex, ThisType) Eclipse::Replication::ReplicatedVariable<ThisType> Repl##Name{#Name, this, Auto, ReplicatedIndex, ReplicationIndex, &ThisType::Name##_OnRep}
#define ONREPPEDFUNCTIONDEF(Name) void Name##_OnRep()

#define REPLICATED_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue, ThisType) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue}; \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, true, Name.ReplicatedVariableIndex, ThisType)

#define REPLICATED_SERIALIZED_FIELD(Type, Name, ThisType) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true}; \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, true, Name.ReplicatedVariableIndex, ThisType)

#define REPLICATED_SERIALIZED_FIELD_DEFAULT_MIN_MAX(Type, Name, DefaultValue, Min, Maxx, ThisType) \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, true, Name.ReplicatedVariableIndex, ThisType)

#define REPLICATED_SERIALIZED_FIELD_MIN_MAX(Type, Name, Min, Max, ThisType) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, Min, Max}; \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, true, Name.ReplicatedVariableIndex, ThisType)

#define REPLICATED_PRIVATE_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue, ThisType) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false, DefaultValue}; \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, true, Name.ReplicatedVariableIndex, ThisType)

#define REPLICATED_PRIVATE_SERIALIZED_FIELD(Type, Name, ThisType) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false};  \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, true, Name.ReplicatedVariableIndex, ThisType)




#define MANUAL_REPLICATED_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue, ThisType) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue}; \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, false, Name.ReplicatedVariableIndex, ThisType)

#define MANUAL_REPLICATED_SERIALIZED_FIELD(Type, Name, ThisType) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true}; \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, false, Name.ReplicatedVariableIndex, ThisType)

#define MANUAL_REPLICATED_SERIALIZED_FIELD_DEFAULT_MIN_MAX(Type, Name, DefaultValue, Min, Max, ThisType) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, DefaultValue, Min, Max}; \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, false, Name.ReplicatedVariableIndex, ThisType)

#define MANUAL_REPLICATED_SERIALIZED_FIELD_MIN_MAX(Type, Name, Min, Max, ThisType) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, true, Min, Max}; \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, false, Name.ReplicatedVariableIndex, ThisType)

#define MANUAL_REPLICATED_PRIVATE_SERIALIZED_FIELD_DEFAULT(Type, Name, DefaultValue, ThisType) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false, DefaultValue}; \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, false, Name.ReplicatedVariableIndex, ThisType)

#define MANUAL_REPLICATED_PRIVATE_SERIALIZED_FIELD(Type, Name, ThisType) \
Eclipse::Reflection::SerializedVariable<Type> Name{#Name, this, false};  \
ONREPPEDFUNCTIONDEF(Name); \
REPLICATEHELPERMACRONOTUSE(Name, false, Name.ReplicatedVariableIndex, ThisType)