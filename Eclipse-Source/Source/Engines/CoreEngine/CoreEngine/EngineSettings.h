#pragma once

#include "Settings.h"

namespace Eclipse
{
	class EngineSettings : public Settings
	{
	public:
		using Settings::Settings;

	public:
		std::string GetEngineName() { return Get<std::string>("Engine_Name"); }
	};
}