#include "SerializedVariable.h"

#include "ReflectionTypeChecks.h"
#include "SerializedEnum.hpp"
#include "DebugLogger.h"

#include "ImGui/ImGui/imgui.h"

#include "Math/Math.h"

namespace Eclipse::Reflection
{
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

	template<typename T>
	bool ComboEnum(const char* label, T& e, int count) {
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
		ImGui::Text(GetName());
		ImGui::SameLine();
		if constexpr (std::is_same<T, float>::value) ImGui::DragFloat((std::string("##Float##") + std::string(GetName())).c_str(), &data, 0.01f);
		else if constexpr (std::is_same<T, bool>::value) ImGui::Checkbox((std::string("##Bool##") + std::string(GetName())).c_str(), &data);
		else if constexpr (std::is_base_of<SerializedEnum, T>::value) ComboEnum((std::string("##Enum##") + std::string(GetName())).c_str(), data, 7);
		else if constexpr (Is_String<T>::value)
		{
			char TemporaryName[256];
			std::strcpy(TemporaryName, data.c_str());

			if (ImGui::InputText((std::string("##String##") + std::string(GetName())).c_str(), TemporaryName, 256, ImGuiInputTextFlags_EnterReturnsTrue))
			{
				data = TemporaryName;
			}
		}

		// Engine Types
		else if constexpr (std::is_same<T, Math::Vector2<float>>::value) ImGui::DragFloat2((std::string("##Vector2Float##") + std::string(GetName())).c_str(), reinterpret_cast<float*>(&data), 0.01f);
		else if constexpr (std::is_same<T, std::vector<Math::Vector2<float>>>::value)
		{
			ResolveTypeInfo();

			size_t vectorSize = sizeof(Math::Vector2<float>);
			size_t itemCount = GetSizeInBytes() / vectorSize;

			ImGui::Dummy({0, 0});

			std::stringstream stream;

			stream << "Size: " << itemCount << "##Vector2CollapsingHeader##";

			if(!ImGui::CollapsingHeader(stream.str().c_str()))
				return;

			for (int i = 0; i < itemCount; i++)
			{
				ImGui::PushID(i);
				Math::Vector2f& floatVec2 = static_cast<Math::Vector2f&>(data[i]);
				ImGui::DragFloat2((std::string("##ListVactorOrWhateverItIsCalledInOurEngineYouCanCallItWhateverYouWantVector2Float##") + std::string(GetName())).c_str(), floatVec2.data, 0.001f);
				ImGui::PopID();
			}
		}

		else ImGui::Text("Type: %s is not supported", typeid(T).name());
	}
}