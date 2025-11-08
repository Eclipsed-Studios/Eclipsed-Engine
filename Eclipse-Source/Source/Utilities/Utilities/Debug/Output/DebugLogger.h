#pragma once

#include <string>
#include <vector>
#include <unordered_map>


#define LOG(string) Eclipse::DebugLogger::Log(string, __FILE__, __LINE__)
#define LOG_WARNING(string) Eclipse::DebugLogger::LogWarning(string, __FILE__, __LINE__)
#define LOG_ERROR(string) Eclipse::DebugLogger::LogError(string, __FILE__, __LINE__)

#define MAX_MESSAGES 10'000

namespace Eclipse
{
	enum class MessageTypes
	{
		Message, Warning, Error
	};

	struct Message final {
		MessageTypes type;
		std::string message;
		std::string timeString;
		std::string file;
		int line;
	};

	namespace Editor
	{
		class ConsoleWindow;
	}

	class DebugLogger final {
		friend class Editor::ConsoleWindow;

	public:
		static void OverwriteDefaultCoutBuffer();

		static void Log(const std::string& aMessage, const char* aFile, int aLine);
		static void LogWarning(const std::string& aMessage, const char* aFile, int aLine);
		static void LogError(const std::string& aMessage, const char* aFile, int aLine);

	private:
		static void AddMessage(const std::string& aMessage, const char* aFile, int aLine, MessageTypes aMessageType);
		static const std::unordered_map<std::string, std::vector<Message>>& GetMessages();

		static void Clear();

	private:
		static inline std::vector<std::string> messageQueue;
		static inline std::unordered_map<std::string, std::vector<Message>> messages;
	};
}