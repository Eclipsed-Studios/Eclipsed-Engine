#include "Replication.h"

#include "NetworkEngine/Shared/Message.h"

#include "NetworkEngine/Server/Server.h"
#include "NetworkEngine/Client/Client.h"

#include "GraphicsEngine/RenderCommands/CommandList.h"
#include "EntityEngine/ComponentManager.h"
#include "EclipsedEngine/Reflection/Registry/ComponentRegistry.h"
#include "EclipsedEngine/Replication/ReplicationManager.h"
#include "EclipsedEngine/Replication/ReplicatedVariable.h"

#include "AssetEngine/Resources.h"

#include <iostream>

namespace Eclipse::Replication
{
	void ReplicationHelper::ClientHelp::RecieveAddComponentMessage(const NetMessage& message)
	{
		// if (!ComponentManager::HasGameObject(message.MetaData.GameObjectID))
		// {
		//     GameObject* gameobject = ComponentManager::CreateGameObject(message.MetaData.GameObjectID);
		//     gameobject->SetIsOwner(true);
		// }

		int ComponentID = 0;
		memcpy(&ComponentID, message.data, sizeof(int));

		int ComponentNameCharCount = 0;
		memcpy(&ComponentNameCharCount, message.data + sizeof(int), sizeof(int));

		char NameBuffer[512];

		memcpy(NameBuffer, message.data + sizeof(int) + sizeof(int), ComponentNameCharCount);
		memset(NameBuffer + ComponentNameCharCount, '\0', 1);

		const char* name = NameBuffer;

		for (auto& component : ComponentManager::GetComponents(message.MetaData.GameObjectID))
		{
			const char* CurrentComponentName = component->GetComponentName();
			if (!memcmp(name, CurrentComponentName, strlen(name)))
				return;
		}

		std::string StringName = name;

		Component* newCompoennt = ComponentRegistry::GetAddComponent(StringName)(message.MetaData.GameObjectID, ComponentID);
		newCompoennt->SetIsOwner(false);
		newCompoennt->IsReplicated = true;

		//ComponentsToStartOnDemand.emplace_back(newCompoennt);

		ComponentsToStartOnDemand.emplace_back(newCompoennt);
		if (ComponentsToStartOnDemand.size() >= myComponentsToRecieved)
		{
			StartReplicatedComponents();
			myComponentsToRecieved = 9999;
		}
	}

	void ReplicationHelper::ClientHelp::RecieveAmountOfComponents(const NetMessage& message)
	{
		memcpy(&myComponentsToRecieved, message.data, sizeof(size_t));
	}

	void ReplicationHelper::ClientHelp::StartReplicatedComponents()
	{
		CommandListManager::GetHappenAtBeginCommandList().Enqueue([]() {
			std::sort(ComponentsToStartOnDemand.begin(), ComponentsToStartOnDemand.end(), [&](Component* aComp0, Component* aComp1)
				{
					return aComp0->GetUpdatePriority() > aComp1->GetUpdatePriority();
				});
			for (Component* component : ComponentsToStartOnDemand)
			{
				component->OnComponentAdded();

				component->Awake();
				component->Start();
			}
			ComponentsToStartOnDemand.clear();
			});
	}

	void ReplicationHelper::ClientHelp::RecieveCreateObjectMessage(const NetMessage& message)
	{
		if (ComponentManager::HasGameObject(message.MetaData.GameObjectID))
			return;

		GameObject* gameobject = ComponentManager::CreateGameObject(message.MetaData.GameObjectID);
		gameobject->SetIsOwner(false);
	}

	void ReplicationHelper::ClientHelp::RecieveDeleteObjectMessage(const NetMessage& message)
	{
		if (!ComponentManager::HasGameObject(message.MetaData.GameObjectID))
			return;

		ComponentManager::Destroy(message.MetaData.GameObjectID);
	}

	void ReplicationHelper::ClientHelp::RecieveRequestVariablesMessage(const NetMessage& message)
	{
		const auto& variableManager = Replication::ReplicationManager::RealReplicatedVariableList;
		for (auto& Component : variableManager)
		{
			for (int i = 0; i < Component.second.size(); i++)
			{
				auto& Variable = Component.second[i];
				if (Variable->ConnectedComponent->IsReplicated)
				{
					Variable->ReplicateThis(i, true);
				}
			}
		}
	}

	void ReplicationHelper::ClientHelp::RecieveVariableMessage(const NetMessage& message)
	{
		unsigned replicationVarIndex = 0;
		unsigned componentID = 0;
		int dataAmount = 0;

		size_t offset = 0;

		memcpy(&componentID, message.data + offset, sizeof(componentID));
		offset += sizeof(componentID);

		memcpy(&replicationVarIndex, message.data + offset, sizeof(replicationVarIndex));
		offset += sizeof(replicationVarIndex);

		memcpy(&dataAmount, message.data + offset, sizeof(dataAmount));
		offset += sizeof(dataAmount);

		auto variableIt = Replication::ReplicationManager::RealReplicatedVariableList.find(componentID);
		if (variableIt == Replication::ReplicationManager::RealReplicatedVariableList.end())
			return;

		Replication::ReplicatedVariable<Component>* Variable = reinterpret_cast<Replication::ReplicatedVariable<Component>*>(variableIt->second[replicationVarIndex]);

		Component* component = Variable->ConnectedComponent;
		const auto& ReppedFunction = Variable->OnRepFunction;

		if (Variable->IsAsset)
		{
			std::string AssetID = "";
			memcpy(&AssetID, message.data + offset, 32);
			RefreshAsset(Variable->myReflectVariable, AssetID);
		}
		else
		{
			void* variableData = Variable->myReflectVariable->GetData();
			memcpy(variableData, message.data + offset, dataAmount);
		}

		(component->*ReppedFunction)();


		/*myReflectVariable->GetData()
			// Debug recieve numbers
			static Math::Vector4f vec;
			memcpy(vec.data, Variable->myReflectVariable->GetData(), dataAmount);
			std::cout << replicationVarID << ", ";
			if (dataAmount > 0)
				std::cout << "  X: " << vec.X;
			if (dataAmount > 4)
				std::cout << "  Y: " << vec.Y;
			if (dataAmount > 8)
				std::cout << "  Z: " << vec.Z;
			if (dataAmount > 12)
				std::cout << "  W: " << vec.Z;
			std::cout << std::endl;
		*/

	}

	void ReplicationHelper::ClientHelp::HandleRecieve(const NetMessage& message)
	{
		switch (message.MetaData.Type)
		{
		case MessageType::Msg_RequestVariables:
		{
			ReplicationHelper::ClientHelp::RecieveRequestVariablesMessage(message);
		}
		break;
		case MessageType::Msg_Variable:
		{
			ReplicationHelper::ClientHelp::RecieveVariableMessage(message);
		}
		break;
		case MessageType::Msg_CreateObject:
		{
			ReplicationHelper::ClientHelp::RecieveCreateObjectMessage(message);
		}
		break;
		case MessageType::Msg_SendMultipleComponents:
		{
			ReplicationHelper::ClientHelp::RecieveAmountOfComponents(message);
		}
		break;
		case MessageType::Msg_DeleteObject:
		{
			ReplicationHelper::ClientHelp::RecieveDeleteObjectMessage(message);
		}
		break;
		case MessageType::Msg_AddComponent:
		{
			ReplicationHelper::ClientHelp::RecieveAddComponentMessage(message);
		}
		break;
		}
	}

	void ReplicationHelper::ClientHelp::RefreshAsset(Reflection::AbstractSerializedVariable* aVariable, std::string aAssetID)
	{
		aVariable->ResolveTypeInfo();

		switch (aVariable->GetType())
		{
		case Eclipse::Reflection::AbstractSerializedVariable::SerializedType_Material:
		{
			Eclipse::Material& material = *(static_cast<Eclipse::Material*>(aVariable->GetData()));
			material = Eclipse::Resources::Get<Eclipse::Material>(aAssetID);
		}
		break;
		case Eclipse::Reflection::AbstractSerializedVariable::SerializedType_AudioClip:
		{
			Eclipse::AudioClip& assset = *(static_cast<Eclipse::AudioClip*>(aVariable->GetData()));
			assset = Eclipse::Resources::Get<Eclipse::AudioClip>(aAssetID);
		}
		break;
		case Eclipse::Reflection::AbstractSerializedVariable::SerializedType_Texture:
		{
			Eclipse::Texture& assset = *(static_cast<Eclipse::Texture*>(aVariable->GetData()));
			assset = Eclipse::Resources::Get<Eclipse::Texture>(aAssetID);
		}
		break;
		}
	}

	void ReplicationHelper::ServerHelp::RequestVariablesFromClient()
	{
		Server& server = Eclipse::MainSingleton::GetInstance<Server>();
		NetMessage msg = NetMessage::BuildGameObjectMessage(0, MessageType::Msg_RequestVariables, nullptr, 0, true);
		server.Send(msg);
	}

	void ReplicationHelper::ServerHelp::SendComponentsScene()
	{
		std::unordered_set<unsigned> ReplicatedGameObjects;

		const auto& variableManager = Replication::ReplicationManager::RealReplicatedVariableList;
		for (auto& Variable : variableManager)
		{
			unsigned gameobjectID = Variable.second[0]->ConnectedComponent->gameObject->GetID();
			ReplicatedGameObjects.emplace(gameobjectID);
		}

		int ComponentCount = 0;

		const std::vector<Component*>& allComponents = ComponentManager::GetAllComponents();
		for (const auto& component : allComponents)
		{
			if (component->IsReplicated && component->IsOwner())
				ComponentCount++;
		}

		Server& server = Eclipse::MainSingleton::GetInstance<Server>();

		NetMessage msg = NetMessage::BuildGameObjectMessage(0, MessageType::Msg_SendMultipleComponents, &ComponentCount, sizeof(unsigned), true);
		server.Send(msg);

		int size = server.GetEndpoints().size();
		for (auto& endpoint : server.GetEndpoints())
		{

			for (const auto& gameobject : ReplicatedGameObjects)
			{
				std::vector<Component*> components = ComponentManager::GetComponents(gameobject);

				for (const auto& component : components)
				{
					if (!component->IsReplicated)
						continue;

					NetMessage message;
					Replication::ReplicationManager::CreateComponentMessage(component, message, true);

					static int TotalCoponentMessagesRecieved = 0;

					Server& server = Eclipse::MainSingleton::GetInstance<Server>();

					server.Send(message, endpoint, [ComponentCount, size]()
						{
							if (TotalCoponentMessagesRecieved++ >= ComponentCount * size)
							{
								//RequestVariablesFromClient();
							}

							return;
						});
				}

			}
		}
	}

	void ReplicationHelper::ServerHelp::HandleRequestedScene()
	{
		//SendComponentScene();
	}

	void ReplicationHelper::ServerHelp::HandleRecieve(const NetMessage& aMessage)
	{
		switch (aMessage.MetaData.Type)
		{
		case MessageType::Msg_RequestSceneInfo:
			HandleRequestedScene();
			break;

		default:
			break;
		}
	}
}