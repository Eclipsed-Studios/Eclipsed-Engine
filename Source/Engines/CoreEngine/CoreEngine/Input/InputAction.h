#pragma once

#include <vector>
#include <string>
#include "rapidjson/rapidjson/document.h"

#include "Keycodes.h"

namespace ENGINE_NAMESPACE
{
	enum class InputActionType
	{
		Axis, Single, Combo
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

		Keycode positiveButton = {};
		Keycode negativeButton = {};

		Keycode button = {};
		
		std::vector<Keycode> comboButtons;

		std::string name;
		
	private:
		int value = 0;

	private:
		void Update();

		rapidjson::Value Save(rapidjson::Document::AllocatorType& anAllocator);
		void Load(const rapidjson::Value& aValue);

		int GetSingleKey();
		int GetAxis();
		int GetCombo();

		bool GetKey(Keycode aKey, InputActionButtonType aButtonType);
	};
}