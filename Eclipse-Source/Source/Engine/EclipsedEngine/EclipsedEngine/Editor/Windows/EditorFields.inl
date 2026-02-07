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
	struct EditorFieldDrawer<int>
	{ 
		static bool Draw(int& aValue)
		{
			return ImGui::DragInt(GetFieldKey().c_str(), &aValue);
		}
	};

	template<>
	struct EditorFieldDrawer<float>
	{ 
		static bool Draw(float& aValue)
		{
			return ImGui::DragFloat(GetFieldKey().c_str(), &aValue);
		}
	};

	template<>
	struct EditorFieldDrawer<bool>
	{
		static bool Draw(bool& aValue)
		{
			return ImGui::Checkbox(GetFieldKey().c_str(), &aValue);
		}
	};

	template<typename U>
	struct EditorFieldDrawer<Math::Vector2<U>>
	{
		static bool Draw(Math::Vector2<U>& aValue)
		{
			return ImGui::DragScalarN(GetFieldKey().c_str(), GetImGuiType<U>(), &aValue.x, 2);
		}
	};

	template<typename U>
	struct EditorFieldDrawer<Math::Vector3<U>>
	{
		static bool Draw(Math::Vector3<U>& aValue)
		{
			return ImGui::DragScalarN(GetFieldKey().c_str(), GetImGuiType<U>(), &aValue.x, 3);
		}
	};

	template<typename U>
	struct EditorFieldDrawer<Math::Vector4<U>>
	{
		static bool Draw(Math::Vector4<U>& aValue)
		{
			return ImGui::DragScalarN(GetFieldKey().c_str(), GetImGuiType<U>(), &aValue.x, 4);
		}
	};

	template<>
	struct EditorFieldDrawer<std::string>
	{
		static bool Draw(std::string& aValue)
		{
			char TemporaryName[256];
			std::strcpy(TemporaryName, aValue.c_str());

			if (ImGui::InputText(GetFieldKey().c_str(), TemporaryName, 256, ImGuiInputTextFlags_EnterReturnsTrue))
			{
				memcpy(aValue.data(), &TemporaryName, strlen(TemporaryName) + 1);
				return true;
			}

			return false;
		}
	};
}