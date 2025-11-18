#pragma once

namespace Eclipse
{
	enum MessageType
	{
		Msg_Connect,
		Msg_Disconnect,

		Msg_CreateObject,
		Msg_AddComponent,

		Msg_Variable,

		Msg_Custom,
	};

	struct Message
	{
	public:
		~Message() = default;

		struct MetaData
		{
			bool IsGarantied;
			bool SentGarantied;
			bool Trash[2];
			int messageID;

			MessageType msgType;
			int GameObjectID;
			size_t dataSize;
		} MetaData;

		char data[512 - sizeof(MetaData)];

	public:
		static inline Message BuildGameObjectMessage(int aGameObjectID, MessageType messageType, const void* data, size_t aByteSize, bool IsGarantied)
		{
			Message message;

			static int messageIDIncrementor = 0;

			message.MetaData.IsGarantied = IsGarantied;
			message.MetaData.SentGarantied = true;
			message.MetaData.messageID = ++messageIDIncrementor;

			message.MetaData.msgType = messageType;
			message.MetaData.GameObjectID = aGameObjectID;
			message.MetaData.dataSize = aByteSize;

			memcpy(message.data, data, aByteSize);

			message.MetaData.dataSize += sizeof(Message::MetaData);

			return message;
		}
	};
}