#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace Eclipse
{
	enum class MessageTypes
	{
		Message, Warning, Error
	};

	struct Message final {
		MessageTypes type;
		std::string timeString;
	};

	namespace Editor
	{
		class ConsoleWindow;
	}

	class DebugLogger final {
		friend class Editor::ConsoleWindow;

	public:
		static void Log(const std::string& aMessage);
		static void LogWarning(const std::string& aMessage);
		static void LogError(const std::string& aMessage);

	private:
		static void AddMessage(const std::string& aMessage, MessageTypes aMessageType);
		static const std::unordered_map<std::string, std::vector<Message>>& GetMessaes();

		static void Clear();

	private:
		static inline std::unordered_map<std::string, std::vector<Message>> messages;
	};
}