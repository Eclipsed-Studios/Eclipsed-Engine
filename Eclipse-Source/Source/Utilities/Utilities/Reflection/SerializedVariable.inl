#include "SerializedVariable.h"

#include "ReflectionTypeChecks.h"
#include "SerializedEnum.hpp"
#include "DebugLogger.h"

#include "ImGui/ImGui/imgui.h"

#include "Math/Math.h"
#include "Reflection/ReflectionTypeChecks.h"

namespace Eclipse::Reflection
{

#ifdef _EDITOR
	template<typename T>
	inline SerializedVariable<T>::SerializedVariable(const char* aName, Component* aCompPtr, bool drawInspector)
		: AbstractSerializedVariable(aName, aCompPtr, drawInspector)
	{
	}

	template<typename T>
	inline SerializedVariable<T>::SerializedVariable(const char* aName, Component* aCompPtr, bool drawInspector, const T& aDefaultValue)
		: AbstractSerializedVariable(aName, aCompPtr, drawInspector), data(aDefaultValue)
	{
	}

	template<typename T>
	inline SerializedVariable<T>::SerializedVariable(const char* aName, Component* aCompPtr, bool drawInspector, T _min, T _max)
		: AbstractSerializedVariable(aName, aCompPtr, drawInspector), myMin(_min), myMax(_max), hasMinMax(true)
	{
	}

	template<typename T>
	inline SerializedVariable<T>::SerializedVariable(const char* aName, Component* aCompPtr, bool drawInspector, const T& aDefaultValue, T _min, T _max)
		: AbstractSerializedVariable(aName, aCompPtr, drawInspector), data(aDefaultValue), myMin(_min), myMax(_max), hasMinMax(true)
	{
	}
#else
	template<typename T>
	inline SerializedVariable<T>::SerializedVariable(const char* aName, Component* aCompPtr)
		: AbstractSerializedVariable(aName, aCompPtr)
	{
	}

	template<typename T>
	inline SerializedVariable<T>::SerializedVariable(const char* aName, Component* aCompPtr, const T& aDefaultValue)
		: AbstractSerializedVariable(aName, aCompPtr), data(aDefaultValue)
	{
	}
#endif



	template<typename T>
	inline void* SerializedVariable<T>::GetData()
	{
		if constexpr (Is_Array<T>::value)
		{
			return &data[0];
		}

		else if constexpr (Is_Vector<T>::value)
		{
			return &data[0];
		}

		else return &data;
	}

	template<typename T>
	inline void SerializedVariable<T>::ResolveTypeInfo()
	{
		if constexpr (Is_String<T>::value)
		{
			type = SerializedType_String;
			sizePerElement = sizeof(char);
			if constexpr (Is_C_String<T>::value) count = std::strlen(data);
			else if constexpr (Is_Std_String<T>::value) count = data.size();
		}

		else if constexpr (Is_Serializable<T>::value)
		{
			type = SerializedType_Custom_Type;
			sizePerElement = sizeof(T);
		}

		else if constexpr (std::is_arithmetic<T>::value)
		{
			type = SerializedType_Fundamental;
			sizePerElement = sizeof(T);
		}

		else if constexpr (Is_Array<T>::value)
		{
			type = SerializedType_Array;
			if constexpr (Is_C_Array<T>::value) count = 0; // C_ArrayCount(data);
			else if constexpr (Is_Std_Array<T>::value) count = data.size();

			sizePerElement = sizeof(data[0]);
		}

		else if constexpr (Is_Vector<T>::value)
		{
			type = SerializedType_List;
			count = data.size();
			sizePerElement = sizeof(data[0]);
		}

		else if constexpr (std::is_base_of<SerializedEnum, T>::value)
		{
			type = SerializedType_Enum;
			sizePerElement = sizeof(T::e);
		}
		else
		{

		}
	}

	template<typename T>
	inline void SerializedVariable<T>::Resize(const size_t& size)
	{
		if constexpr (Is_Vector<T>::value) data.resize(size);
	}


#ifdef _EDITOR
	template<typename T>
	bool ComboEnum(const char* label, T& e) {
		unsigned currentIndex = static_cast<unsigned>(e);
		bool changed = false;

		if (ImGui::BeginCombo(label, T::AsString(T(currentIndex)).c_str()))
		{
			for (const T& val : T::List)
			{
				bool isSelected = (currentIndex == val);
				std::string name = T::AsString(val);

				if (ImGui::Selectable(name.c_str(), isSelected)) {
					e = static_cast<T>(val);
					changed = true;
				}
				if (isSelected) {
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		return changed;
	}

	template<typename T>
	inline void SerializedVariable<T>::DrawInspector()
	{

		if constexpr (Is_Vector<T>::value || Is_Array<T>::value)
		{
			isDrawn = ImGui::CollapsingHeader(GetName());

			if (!isDrawn) return;

			ResolveTypeInfo();
			for (int i = 0; i < GetCount(); ++i)
			{
				ImGui::Dummy({ 20, 0 });
				ImGui::SameLine();

				ImGui::PushID(i);

				if constexpr (Is_Vector<T>::value)
				{
					ImGui::SameLine();

					if (ImGui::Button("-"))
					{
						data.erase(data.begin() + i);
						ImGui::PopID();
						return;
					}

					ImGui::SameLine();
				}

				DrawElement(data[i]);
				ImGui::PopID();
			}

			if constexpr (Is_Vector<T>::value)
			{
				ImGui::Dummy({ 20, 0 });
				ImGui::SameLine();

				if (ImGui::Button("Add"))
				{
					data.push_back({});
				}
			}
		}
		else
		{
			ImGui::Text(GetName());
			ImGui::SameLine();
			DrawElement(data);
		}
	}

	template<typename T>
	template<typename U>
	inline void SerializedVariable<T>::DrawElement(U& element)
	{
		float availX = ImGui::GetContentRegionAvail().x;

		ImGui::SetNextItemWidth(availX);

		if constexpr (std::is_same<U, float>::value) ImGui::DragFloat(GetNameID().c_str(), &element, 0.001f, hasMinMax ? myMin : 0.f, hasMinMax ? myMax : 0.f);
		else if constexpr (std::is_same<U, int>::value) ImGui::DragInt(GetNameID().c_str(), &element, 1.f, hasMinMax ? myMin : 0, hasMinMax ? myMax : 0);
		else if constexpr (std::is_same<U, Math::Vector2<float>>::value) ImGui::DragFloat2(GetNameID().c_str(), &element.x, 0.001f);
		else if constexpr (std::is_same<U, bool>::value) ImGui::Checkbox(GetNameID().c_str(), &element);
		else if constexpr (Is_String<U>::value) DrawString(data);
		else if constexpr (std::is_base_of<SerializedEnum, U>::value) ComboEnum(GetNameID().c_str(), element);

		else ImGui::Text("Type: %s is not supported", typeid(T).name());
	}

	template<typename T>
	template<typename U>
	inline void SerializedVariable<T>::DrawString(U& element)
	{
		char TemporaryName[256];
		std::strcpy(TemporaryName, element.c_str());

		if (ImGui::InputText(GetName(), TemporaryName, 256, ImGuiInputTextFlags_EnterReturnsTrue))
		{
			element = TemporaryName;
		}
	}
#endif
}