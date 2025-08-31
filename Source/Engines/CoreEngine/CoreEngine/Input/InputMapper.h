#pragma once

#include "Keycodes.h"

#include <string>
#include <vector>
#include <functional>
#include "rapidjson/rapidjson/document.h"

namespace ENGINE_NAMESPACE
{
	enum class InputActionType
	{
		Axis, Single
	};

	enum class InputActionButtonType
	{
		Repeated, Down, Up
	};

	struct InputAction
	{
		friend class InputMapper;

		InputAction() = default;
		InputAction(const std::string& actionName) : name(actionName) {}

		InputActionType type = {};
		InputActionButtonType buttonType = {};

		Keycode negativeButton = {};
		Keycode positiveButton = {};

		Keycode button = {};

	private:
		std::string name;
		int value = 0;

	private:
		void Update();

		rapidjson::Value Save(rapidjson::Document::AllocatorType& anAllocator);
		void Load(const rapidjson::Value& aValue);
	};


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