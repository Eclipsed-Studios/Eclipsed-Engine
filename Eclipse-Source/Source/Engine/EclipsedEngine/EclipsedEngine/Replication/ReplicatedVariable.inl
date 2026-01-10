#include "ReplicatedVariable.h"
#include "ReplicationManager.h"

#include "Eclipsedengine/Reflection/Reflection.h"
#include "CoreEngine/MainSingleton.h"

#include "NetworkEngine/Server/Server.h"
#include "NetworkEngine/Client/Client.h"

#include "EclipsedEngine/Components/Component.h"
#include "EntityEngine/GameObject.h"

namespace Eclipse::Replication
{
   template<typename T>
   ReplicatedVariable<T>::ReplicatedVariable(std::string aName, Component* aComponent, bool anAutomatic, unsigned ID, void(T::* OnRepFunctionPtr)()) : OnRepFunction(OnRepFunctionPtr)
   {
       ConnectedComponent = aComponent;

       bool variableExist = false;

       auto& reflectionList = Reflection::ReflectionManager::GetList();
       auto& variableList = reflectionList.at(aComponent);

       for (auto& variable : variableList)
       {
           if (variable->GetName() == aName)
           {
               variable->ResolveTypeInfo();
               ManualVariableSending = !anAutomatic;
               myReflectVariable = variable;
               
               dataAmount = variable->GetSizeInBytes();
               variableExist = true;
               break;
           }
       }

       assert(variableExist);

       ReplicationManager::EmplaceReplicatedVariable(ID, this);
   }
}