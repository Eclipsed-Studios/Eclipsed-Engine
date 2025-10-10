#include "InputAction.h"

#include "rapidjson/rapidjson/writer.h"
#include "rapidjson/rapidjson/stringbuffer.h"
#include "rapidjson/rapidjson/filewritestream.h"

#include "Keycodes.h"
#include "Input.h"

namespace Eclipse
{
	void InputAction::Update()
	{
		switch (type)
		{
		case InputActionType::Axis: value = GetAxis();
			break;
		case InputActionType::Single: value = GetSingleKey();
			break;
		case InputActionType::Combo: value = GetCombo();
			break;
		}
	}



	rapidjson::Value InputAction::Save(rapidjson::Document::AllocatorType& anAllocator)
	{
		using namespace rapidjson;

		Value action(kObjectType);
		action.AddMember(stringify(name), Value(name.c_str(), anAllocator).Move(), anAllocator);
		action.AddMember(stringify(type), (int)type, anAllocator);
		action.AddMember(stringify(buttonType), (int)buttonType, anAllocator);

		if (type == InputActionType::Single)
		{
			action.AddMember(stringify(button), (int)button, anAllocator);
		}
		else if (type == InputActionType::Combo)
		{
			Value combo(kArrayType);
			for (const Keycode::Scancode& key : comboButtons)
			{
				combo.PushBack((int)key, anAllocator);
			}

			action.AddMember(stringify(comboButtons), combo, anAllocator);
		}
		else
		{
			action.AddMember(stringify(positiveButton), (int)positiveButton, anAllocator);
			action.AddMember(stringify(negativeButton), (int)negativeButton, anAllocator);
		}

		return action;
	}

	void InputAction::Load(const rapidjson::Value& aValue)
	{
		name = aValue[stringify(name)].GetString();
		type = (InputActionType)aValue[stringify(type)].GetInt();
		buttonType = (InputActionButtonType)aValue[stringify(buttonType)].GetInt();

		if (type == InputActionType::Axis)
		{
			positiveButton = (Keycode::Scancode)aValue[stringify(positiveButton)].GetInt();
			negativeButton = (Keycode::Scancode)aValue[stringify(negativeButton)].GetInt();
		}
		else if (type == InputActionType::Combo)
		{
			const auto& comboArray = aValue[stringify(comboButtons)];
			if (comboArray.IsArray())
			{
				comboButtons.clear();
				for (auto& v : comboArray.GetArray())
				{
					comboButtons.push_back((Keycode::Scancode)v.GetInt());
				}
			}
		}
		else
		{
			button = (Keycode::Scancode)aValue[stringify(button)].GetInt();
		}
	}
	int InputAction::GetSingleKey()
	{
		return GetKey(button, buttonType);
	}

	int InputAction::GetAxis()
	{
		return GetKey(positiveButton, buttonType) - GetKey(negativeButton, buttonType);
	}
	int InputAction::GetCombo()
	{
		for (const Keycode::Scancode& key : comboButtons)
		{
			if (!Input::GetKey(key))
			{
				return 0;
			}
		}

		return true;
	}
	bool InputAction::GetKey(Keycode::Scancode aKey, InputActionButtonType aButtonType)
	{
		switch (buttonType)
		{
		case InputActionButtonType::Repeated: return Input::GetKey(aKey);
		case InputActionButtonType::Down: return Input::GetKeyDown(aKey);
		case InputActionButtonType::Up: return Input::GetKeyUp(aKey);
		}

		return false;
	}
}