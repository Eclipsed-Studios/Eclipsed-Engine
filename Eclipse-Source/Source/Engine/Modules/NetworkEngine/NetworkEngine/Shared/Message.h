#pragma once

#include <string>

namespace Eclipse
{
	enum MessageType
	{
		Msg_Connect,
		Msg_Disconnect,

		Msg_CreateObject,
		Msg_DeleteObject,
		Msg_AddComponent,
		
		Msg_Variable,
		
		Msg_RequestSceneInfo,
		Msg_SentAllObjects,

		Msg_Custom,
	};

	struct NetMessage
	{
	public:
		~NetMessage() = default;

		struct MetaData
		{
			bool IsGarantied;
			bool SentGarantied;
			bool Trash[2];
			int messageID;

			MessageType Type;
			unsigned GameObjectID;
			int dataSize;
		} MetaData;

		char data[512 - sizeof(MetaData)];

	public:
		static inline NetMessage BuildGameObjectMessage(unsigned aGameObjectID, MessageType messageType, const void* data, int aByteSize, bool IsGarantied)
		{
			NetMessage message;

			static int messageIDIncrementor = 0;

			message.MetaData.IsGarantied = IsGarantied;
			message.MetaData.SentGarantied = true;
			message.MetaData.messageID = ++messageIDIncrementor;

			message.MetaData.Type = messageType;
			message.MetaData.GameObjectID = aGameObjectID;
			message.MetaData.dataSize = aByteSize;

			memcpy(message.data, data, aByteSize);

			message.MetaData.dataSize += sizeof(NetMessage::MetaData);

			return message;
		}
	};
}