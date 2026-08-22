#pragma once

#include <string>

#include "EclipsedEngine.Core.hpp"

namespace Eclipse
{
	enum class DiagnosticSeverity
	{
		Info, 
		Warning,
		Error
	};

	enum class DiagnosticKind
	{
		Text,
		SourceCode 
	};

	struct ECL_API DebugMessage
	{
		DiagnosticSeverity diagnosticSeverity = DiagnosticSeverity::Info;
		DiagnosticKind diagnosticKind = DiagnosticKind::Text;

		std::string message = "";
		std::string file;

		std::string timeStamp = "";
		
		int line = -1;
	};
}

