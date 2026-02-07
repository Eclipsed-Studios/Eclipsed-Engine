#pragma once

#include <vector>
#include <type_traits>
#include "ImGui/imgui.h"

namespace Eclipse::Editor
{
	class EditorField
	{
	public:
		template<typename T>
		static void Draw(T& aValue)
		{
			using Clean = std::remove_pointer_t<std::remove_cvref_t<T>>;

			if constexpr (std::is_base_of_v<Component, Clean>)
			{
				InternalDraw<Component>(static_cast<Component&>(aValue));
			}
			else
			{
				InternalDraw<Clean>(aValue);
			}
		}

		template<typename T>
		static ImGuiDataType_ GetImGuiType()
		{
			using Clean = std::remove_pointer_t<std::remove_cvref_t<T>>;

			if constexpr (std::is_same_v<Clean, char>) return ImGuiDataType_S8;
			else if constexpr (std::is_same_v<Clean, unsigned char>) return ImGuiDataType_U8;
			else if constexpr (std::is_same_v<Clean, short>) return ImGuiDataType_S16;
			else if constexpr (std::is_same_v<Clean, unsigned short>) return ImGuiDataType_U16;
			else if constexpr (std::is_same_v<Clean, int>) return ImGuiDataType_S32;
			else if constexpr (std::is_same_v<Clean, unsigned int>) return ImGuiDataType_U32;
			else if constexpr (std::is_same_v<Clean, long long>) return ImGuiDataType_S64;
			else if constexpr (std::is_same_v<Clean, unsigned long long>) return ImGuiDataType_U64;
			else if constexpr (std::is_same_v<Clean, float>) return ImGuiDataType_Float;
			else if constexpr (std::is_same_v<Clean, double>) return ImGuiDataType_Double;
			else if constexpr (std::is_same_v<Clean, bool>) return ImGuiDataType_Bool;
			else if constexpr (std::is_same_v<Clean, std::string>) return ImGuiDataType_String;
			else static_assert("Type not supported.");
		}

	private:
		template<typename T>
		static bool InternalDraw(T& aValue)
		{
			static_assert("The method template is not implemented for: " + typeid(T).name());
		}
	};
}

#include "EditorFields.inl"