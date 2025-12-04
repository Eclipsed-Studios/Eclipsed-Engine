#include "Client.h"

#include "GraphicsEngine/RenderCommands/CommandList.h"

#include "NetworkEngine/Replication/ReplicatedVariable.h"
#include "NetworkEngine/Shared/Message.h"

#include <iostream>

namespace Eclipse
{
	void Client::AddComponentMessage(const NetMessage& message)
	{
		int ComponentNameCharCount = 0;
		memcpy(&ComponentNameCharCount, message.data, sizeof(int));

		char NameBuffer[512];

		memcpy(NameBuffer, message.data + sizeof(int), ComponentNameCharCount);
		memset(NameBuffer + ComponentNameCharCount, '\0', 1);

		const char* name = NameBuffer;

		for (auto& component : ComponentManager::GetComponents(message.MetaData.GameObjectID))
		{
			const char* CurrentComponentName = component->GetComponentName();
			if (!memcmp(name, CurrentComponentName, strlen(name)))
				return;
		}
		std::string STRname = name;

		CommandListManager::GetHappenAtBeginCommandList().Enqueue([STRname, goid = message.MetaData.GameObjectID]{
			Component* newCompoennt = ComponentRegistry::GetInspectorAddComponent(STRname)(goid);

			newCompoennt->Awake();
			newCompoennt->Start();
		});
	}

	void Client::CreateObjectMessage(const NetMessage& message)
	{
		if (!ComponentManager::HasGameObject(message.MetaData.GameObjectID))
			ComponentManager::CreateGameObject(message.MetaData.GameObjectID);
	}

	void Client::VariableMessage(const NetMessage& message)
	{
		int replicationVarID = 0;
		int dataAmount = 0;

		size_t offset = 0;

		memcpy(&replicationVarID, message.data + offset, sizeof(replicationVarID));
		offset += sizeof(replicationVarID);

		memcpy(&dataAmount, message.data + offset, sizeof(dataAmount));
		offset += sizeof(dataAmount);

		auto variableIt = Replication::ReplicationManager::ReplicatedVariableList.find(replicationVarID);
		if (variableIt == Replication::ReplicationManager::ReplicatedVariableList.end())
			return;

		Replication::ReplicatedVariable<Component>* Variable = reinterpret_cast<Replication::ReplicatedVariable<Component>*>(variableIt->second);

		Component* component = Variable->ConnectedComponent;
		const auto& ReppedFunction = Variable->OnRepFunction;

		(component->*ReppedFunction)();

		void* variableData = Variable->myVariableAddress;
		memcpy(variableData, message.data + offset, dataAmount);

		offset += dataAmount;


		// // Debug recieve numbers
// static Math::Vector4f vec;
// memcpy(vec.data, variableIt->second->myVariableAddress, dataAmount);
// std::cout << replicationVarID << ", ";
// if (dataAmount > 0)
//     std::cout << "  X: " << vec.X;
// if (dataAmount > 4)
//     std::cout << "  Y: " << vec.Y;
// if (dataAmount > 8)
//     std::cout << "  Z: " << vec.Z;
// if (dataAmount > 12)
//     std::cout << "  W: " << vec.Z;

// std::cout << std::endl;
	}

	void Client::HandleRecieve(const NetMessage& message)
	{
		switch (message.MetaData.Type)
		{
		case MessageType::Msg_Variable:
		{
			VariableMessage(message);
		}
		break;
		case MessageType::Msg_CreateObject:
		{
			CreateObjectMessage(message);
		}
		break;
		case MessageType::Msg_AddComponent:
		{
			AddComponentMessage(message);
		}
		break;
		}
	}
}