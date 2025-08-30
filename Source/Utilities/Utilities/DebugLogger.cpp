#include "DebugLogger.h"

#include <chrono>
#include <ctime>
namespace ENGINE_NAMESPACE::Editor
{
	void DebugLogger::Log(const std::string& aMessage)
	{
		AddMessage(aMessage, MessageTypes::Message);
	}

	void DebugLogger::LogWarning(const std::string& aMessage)
	{
		AddMessage(aMessage, MessageTypes::Warning);
	}

	void DebugLogger::LogError(const std::string& aMessage)
	{
		AddMessage(aMessage, MessageTypes::Error);
	}

	void DebugLogger::AddMessage(const std::string& aMessage, MessageTypes aMessageType)
	{
		const auto now = std::time(nullptr);
		const auto currentTime = std::localtime(&now);

		std::stringstream timeString;
		timeString << std::put_time(currentTime, "%H:%M:%S");

		Message message;
		message.type = aMessageType;
		message.timeString = timeString.str();

		messages[aMessage].emplace_back(message);
	}

	const std::unordered_map<std::string, std::vector<Message>>& DebugLogger::GetMessaes() { return messages; }

	void DebugLogger::Clear() { messages.clear(); }

}