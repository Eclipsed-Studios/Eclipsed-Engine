#pragma once

#ifdef ECLIPSED_EDITOR
#include "CoreEngine/Containers/RingBuffer.h"
#include <string>
#include "DebugMessage.h"
#include "DebugMessageFactory.h"

namespace Eclipse::Core
{
#define DEBUG_LOGGER_BUFFER_SIZE 40'000

	class DebugLogger
	{
	public:
		friend class ConsoleWindow;

	public:
		static void AddMessage(const DebugMessage& message);

		static const RingBuffer<DebugMessage, DEBUG_LOGGER_BUFFER_SIZE>& GetMessages();
		static void Clear();

	private:
		static RingBuffer<DebugMessage, DEBUG_LOGGER_BUFFER_SIZE> messageBuffer;
	};
}

#define CORE_LOG_CODE(MESSAGE) Eclipse::Core::DebugLogger::AddMessage(Eclipse::DebugMessageFactory::ConstructSourceCodeMessage(MESSAGE, __FILE__, __LINE__, Eclipse::DiagnosticSeverity::Info))
#define CORE_LOG_WARNING_CODE(MESSAGE) Eclipse::Core::DebugLogger::AddMessage(Eclipse::DebugMessageFactory::ConstructSourceCodeMessage(MESSAGE, __FILE__, __LINE__, Eclipse::DiagnosticSeverity::Warning))
#define CORE_LOG_ERROR_CODE(MESSAGE) Eclipse::Core::DebugLogger::AddMessage(Eclipse::DebugMessageFactory::ConstructSourceCodeMessage(MESSAGE, __FILE__, __LINE__, Eclipse::DiagnosticSeverity::Error))

#define CORE_LOG(MESSAGE) Eclipse::Core::DebugLogger::AddMessage(Eclipse::DebugMessageFactory::ConstructTextMessage(MESSAGE, Eclipse::DiagnosticSeverity::Info))
#define CORE_LOG_WARNING(MESSAGE) Eclipse::Core::DebugLogger::AddMessage(Eclipse::DebugMessageFactory::ConstructTextMessage(MESSAGE, Eclipse::DiagnosticSeverity::Warning))
#define CORE_LOG_ERROR(MESSAGE) Eclipse::Core::DebugLogger::AddMessage(Eclipse::DebugMessageFactory::ConstructTextMessage(MESSAGE, Eclipse::DiagnosticSeverity::Error))
#else
#define CORE_LOG(MESSAGE)
#define CORE_LOG_WARNING(MESSAGE)
#define CORE_LOG_ERROR(MESSAGE)
#endif