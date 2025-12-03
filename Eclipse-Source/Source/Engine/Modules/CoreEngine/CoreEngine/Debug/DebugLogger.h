#pragma once

#ifdef ECLIPSED_EDITOR
#include "CoreEngine/Containers/RingBuffer.h"
#include <string>

namespace Eclipse
{
	class DebugLogger
	{
		enum class MessageTypes;
		struct ConsoleMessage;

	public:
		static void AddMessage(const std::string& aMessage, const char* aFile, int aLine, MessageTypes aMessageType);

		static const RingBuffer<ConsoleMessage, 10'000>& GetMessages();
		static void Clear();

	public:
		enum class MessageTypes
		{
			Message, Warning, Error
		};

		struct ConsoleMessage
		{
			MessageTypes type;
			std::string message;
			std::string timeString;
			std::string file;
			int line;
		};

	private:
		static RingBuffer<ConsoleMessage, 10'000> messageBuffer;
	};
}

#define LOG(MESSAGE) Eclipse::DebugLogger::AddMessage(MESSAGE, __FILE__, __LINE__, Eclipse::DebugLogger::MessageTypes::Message)
#define LOG_WARNING(MESSAGE) Eclipse::DebugLogger::AddMessage(MESSAGE, __FILE__, __LINE__, Eclipse::DebugLogger::MessageTypes::Warning)
#define LOG_ERROR(MESSAGE) Eclipse::DebugLogger::AddMessage(MESSAGE, __FILE__, __LINE__, Eclipse::DebugLogger::MessageTypes::Error)
#else
#define LOG(MESSAGE)
#define LOG_WARNING(MESSAGE)
#define LOG_ERROR(MESSAGE)
#endif