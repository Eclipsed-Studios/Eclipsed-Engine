#pragma once

#include <unordered_set>
#include <string>
#include <filesystem>

namespace Eclipse
{
	using GUID = std::string;

	class GuidGenerator
	{
	public:
		static std::string Generate();
	};
}