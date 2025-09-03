#pragma once

#include "Keycodes.h"

#include <string>
#include <unordered_map>
#include <vector>
#include "rapidjson/rapidjson/document.h"

#include "InputAction.h"

namespace ENGINE_NAMESPACE
{
	class InputMapper
	{
	public:
		static void Save();
		static void Load();

		static void Update();

	public:
		static int ReadValue(const std::string& actionName);

		static InputAction& AddAction(const std::string& actionName);

	private:

		static inline std::unordered_map<std::string, InputAction> map;
	};
}