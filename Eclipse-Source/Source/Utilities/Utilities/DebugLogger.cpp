#include "DebugLogger.h"

#include <chrono>
#include <ctime>
#include <iostream>

#include "DebugLogBuffer.h"

namespace Eclipse
{
	void DebugLogger::OverwriteDefaultCoutBuffer()
	{
		static DebugLogBuf buffer = DebugLogBuf();
		std::cout.rdbuf(&buffer);
	}

	void DebugLogger::Log(const std::string& aMessage, const char* aFile, int aLine)
	{
		AddMessage(aMessage, aFile, aLine, MessageTypes::Message);
	}

	void DebugLogger::LogWarning(const std::string& aMessage, const char* aFile, int aLine)
	{
		AddMessage(aMessage, aFile, aLine, MessageTypes::Warning);
	}

	void DebugLogger::LogError(const std::string& aMessage, const char* aFile, int aLine)
	{
		AddMessage(aMessage, aFile, aLine, MessageTypes::Error);
	}

	void DebugLogger::AddMessage(const std::string& aMessage, const char* aFile, int aLine, MessageTypes aMessageType)
	{
		const auto now = std::time(nullptr);
		const auto currentTime = std::localtime(&now);

		std::stringstream timeString;
		timeString << std::put_time(currentTime, "%H:%M:%S");

		Message message;
		message.type = aMessageType;
		message.timeString = timeString.str();
		message.file = aFile;
		message.line = aLine;
		message.message = aMessage;

		messages[aMessage].emplace_back(message);
		messageQueue.emplace_back(aMessage);
	}

	const std::unordered_map<std::string, std::vector<Message>>& DebugLogger::GetMessages() { return messages; }

	void DebugLogger::Clear() { messages.clear(); }

}