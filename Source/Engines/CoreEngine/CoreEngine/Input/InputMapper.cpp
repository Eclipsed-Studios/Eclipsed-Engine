#include "InputMapper.h"

#include "Keycodes.h"

#include <string>
#include <functional>

#include "Input/Input.h"

#include "DebugLogger.h"

#include <iostream>
#include <fstream>

#include "rapidjson/rapidjson/document.h"
#include "rapidjson/rapidjson/writer.h"
#include "rapidjson/rapidjson/stringbuffer.h"
#include "rapidjson/rapidjson/filewritestream.h"

#include "defines.h"

namespace ENGINE_NAMESPACE
{
	void InputAction::Update()
	{
		auto getKey = [this](Keycode key) {
			switch (buttonType)
			{
			case InputActionButtonType::Repeated: return Input::GetKey(key);
			case InputActionButtonType::Down: return Input::GetKeyDown(key);
			case InputActionButtonType::Up: return Input::GetKeyUp(key);
			}

			return false;
			};


		if (type == InputActionType::Axis)
		{
			value = getKey(positiveButton) - getKey(negativeButton);
		}
		else if (type == InputActionType::Single)
		{
			value = getKey(button);
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
			positiveButton = (Keycode)aValue[stringify(positiveButton)].GetInt();
			negativeButton = (Keycode)aValue[stringify(negativeButton)].GetInt();
		}
		else
		{
			button = (Keycode)aValue[stringify(button)].GetInt();
		}
	}




	void InputMapper::Save()
	{
		using namespace rapidjson;

		Document d;
		d.SetObject();
		Document::AllocatorType& allocator = d.GetAllocator();

		Value inputList(kArrayType);

		for (auto& [name, inputAction] : map)
		{
			Value action = inputAction.Save(allocator);
			inputList.PushBack(action, allocator);
		}

		d.AddMember("inputActions", inputList, allocator);

		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		d.Accept(writer);

		std::ofstream ofs(ASSET_PATH"inputmap.json");
		ofs << buffer.GetString();
		ofs.close();
	}

	void InputMapper::Load()
	{
		using namespace rapidjson;

		std::ifstream ifs(ASSET_PATH "inputmap.json");
		if (!ifs.is_open()) {
			Save();
		}

		std::string jsonString((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>());

		ifs.close();

		Document d;
		d.Parse(jsonString.c_str());

		if (d.HasMember("inputActions"))
		{
			const Value& inputList = d["inputActions"];
			for (auto& action : inputList.GetArray())
			{
				InputAction inputAction;
				inputAction.Load(action);

				map[inputAction.name] = inputAction;
			}
		}
	}

	void InputMapper::Update()
	{
		for (auto& [name, action] : map)
		{
			action.Update();
		}
	}

	int InputMapper::ReadValue(const std::string& actionName)
	{
		return map[actionName].value;
	}

	InputAction& InputMapper::AddAction(const std::string& actionName)
	{
		map[actionName] = InputAction(actionName);
		return map[actionName];
	}

}