#include "pch.h"

#include "DebugLogger.h"

namespace Eclipse
{
	RingBuffer<DebugLogger::ConsoleMessage, 10'000> DebugLogger::messageBuffer;

	void DebugLogger::AddMessage(const std::string& aMessage, const char* aFile, int aLine, MessageTypes aMessageType)
	{
		const auto now = std::time(nullptr);
		const auto currentTime = std::localtime(&now);

		std::stringstream timeString;
		timeString << std::put_time(currentTime, "%H:%M:%S");

		messageBuffer.Push({
			aMessageType,
			aMessage,
			timeString.str(), 
			aFile,
			aLine });
	}

	const RingBuffer<DebugLogger::ConsoleMessage, 10'000>& DebugLogger::GetMessages()
	{
		return messageBuffer;
	}

	void DebugLogger::Clear()
	{
		messageBuffer.Clear();
	}
}