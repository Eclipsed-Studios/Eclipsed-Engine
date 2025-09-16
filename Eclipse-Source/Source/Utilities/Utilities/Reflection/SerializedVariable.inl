#include "SerializedVariable.h"

#include "ReflectionTypeChecks.h"
#include "SerializedEnum.hpp"
#include "DebugLogger.h"

#include "ImGui/ImGui/imgui.h"

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
		if constexpr(Is_Vector<T>::value) data.resize(size);
	}



	template<typename T>
	inline void SerializedVariable<T>::DrawInspector()
	{
		ImGui::Text(GetName());
		ImGui::SameLine();
		if constexpr (std::is_same<T, float>::value) ImGui::DragFloat((std::string("##float##") + std::string(GetName())).c_str(), &data, 0.01f);
		else if constexpr (std::is_same<T, bool>::value) ImGui::Checkbox((std::string("##bools##") + std::string(GetName())).c_str(), &data);
		//else if constexpr (std::is_base_of<SerializedEnum, T>::value) ComboEnum(std::string("##float##" + GetName()).c_str(), data, 7);
	}
}