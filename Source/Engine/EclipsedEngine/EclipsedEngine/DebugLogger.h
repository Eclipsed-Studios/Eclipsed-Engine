#pragma once

#ifdef ECLIPSED_EDITOR
#include "CoreEngine/Debug/DebugLogger.h"

#include "CoreEngine/Macros/defines.h"

namespace Eclipse
{
	class ECLIPSED_API DebugLogger
	{
	public:
		friend class ConsoleWindow;

	public:
		static void AddMessage(const DebugMessage& message) { Core::DebugLogger::AddMessage(message); }

		static const RingBuffer<DebugMessage, DEBUG_LOGGER_BUFFER_SIZE>& GetMessages() { return Core::DebugLogger::GetMessages(); }
		static void Clear() { return Core::DebugLogger::Clear(); }
	};
}

#define LOG_CODE(MESSAGE) Eclipse::DebugLogger::AddMessage(Eclipse::DebugMessageFactory::ConstructSourceCodeMessage(MESSAGE, __FILE__, __LINE__, Eclipse::DiagnosticSeverity::Info))
#define LOG_WARNING_CODE(MESSAGE) Eclipse::DebugLogger::AddMessage(Eclipse::DebugMessageFactory::ConstructSourceCodeMessage(MESSAGE, __FILE__, __LINE__, Eclipse::DiagnosticSeverity::Warning))
#define LOG_ERROR_CODE(MESSAGE) Eclipse::DebugLogger::AddMessage(Eclipse::DebugMessageFactory::ConstructSourceCodeMessage(MESSAGE, __FILE__, __LINE__, Eclipse::DiagnosticSeverity::Error))

#define LOG(MESSAGE) Eclipse::DebugLogger::AddMessage(Eclipse::DebugMessageFactory::ConstructTextMessage(MESSAGE, Eclipse::DiagnosticSeverity::Info))
#define LOG_WARNING(MESSAGE) Eclipse::DebugLogger::AddMessage(Eclipse::DebugMessageFactory::ConstructTextMessage(MESSAGE, Eclipse::DiagnosticSeverity::Warning))
#define LOG_ERROR(MESSAGE) Eclipse::DebugLogger::AddMessage(Eclipse::DebugMessageFactory::ConstructTextMessage(MESSAGE, Eclipse::DiagnosticSeverity::Error))
#else
#define LOG_CODE(MESSAGE)
#define LOG_WARNING_CODE(MESSAGE)
#define LOG_ERROR_CODE(MESSAGE)
#define LOG(MESSAGE)
#define LOG_WARNING(MESSAGE)
#define LOG_ERROR(MESSAGE)
#endif