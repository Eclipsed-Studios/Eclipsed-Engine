#include "EditorField.h"

#include "ImGui/imgui.h"
#include <random>

#include "CoreEngine/Math/Vector/Vector2.h"
#include "CoreEngine/Math/Vector/Vector3.h"
#include "CoreEngine/Math/Vector/Vector4.h"

#include <vector>
#include <string>

namespace Eclipse::Editor
{
	template<>
	inline bool EditorField::InternalDraw<int>(int& aValue)
	{
		return ImGui::DragInt(std::to_string(rand()).c_str(), &aValue);
	}

	template<typename U>
	inline bool InternalDraw(Math::Vector2<U>& aValue)
	{
		return ImGui::DragScalarN(std::to_string(rand()).c_str(), GetImGuiType<U>(), &aValue.x, 2);
	}

	template<typename U>
	inline bool InternalDraw(Math::Vector3<U>& aValue)
	{
		return ImGui::DragScalarN(std::to_string(rand()).c_str(), GetImGuiType<U>(), &aValue.x, 3);
	}

	template<typename U>
	inline bool InternalDraw(Math::Vector4<U>& aValue)
	{
		return ImGui::DragScalarN(std::to_string(rand()).c_str(), GetImGuiType<U>(), &aValue.x, 4);
	}

	template<typename U>
	inline bool InternalDraw(std::vector<U>& aValue)
	{

	}

	template<>
	inline bool EditorField::InternalDraw<float>(float& aValue)
	{
		return ImGui::DragFloat(std::to_string(rand()).c_str(), &aValue);
	}

	template<>
	inline bool EditorField::InternalDraw<bool>(bool& aValue)
	{
		return ImGui::Checkbox(std::to_string(rand()).c_str(), &aValue);
	}

	template<>
	inline bool EditorField::InternalDraw<std::string>(std::string& aValue)
	{
		char TemporaryName[256];
		std::strcpy(TemporaryName, aValue.c_str());

		if (ImGui::InputText(std::to_string(rand()).c_str(), TemporaryName, 256, ImGuiInputTextFlags_EnterReturnsTrue))
		{
			memcpy(aValue.data(), &TemporaryName, strlen(TemporaryName) + 1);
		}
	}
}