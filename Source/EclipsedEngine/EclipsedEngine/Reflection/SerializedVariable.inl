#include "SerializedVariable.h"

#include "ReflectionTypeChecks.h"
#include "ImGui/imgui.h"

#include "EclipsedEngine/Core/Math/Math.h"

#include <typeindex>

#include "EclipsedEngine/Assets/Assets/MaterialAsset.h"
#include "EclipsedEngine/Assets/Assets/AudioAsset.h"
#include "EclipsedEngine/Assets/Assets/FontAsset.h"
#include "EclipsedEngine/Assets/Assets/PrefabAsset.h"
#include "EclipsedEngine/Assets/Assets/TextureAsset.h"

#include "EclipsedEngine/Core/Math/Random.h"

namespace Eclipse::Reflection
{

	//#ifdef ECL_EDITOR

	template<typename T>
	inline SerializedVariable<T>::SerializedVariable(const char* aName, Component* aCompPtr, bool drawInspector, float aChangeAmount)
		: AbstractSerializedVariable(aName, aCompPtr, drawInspector, aChangeAmount)
	{

	}

	template<typename T>
	inline SerializedVariable<T>::SerializedVariable(const char* aName, Component* aCompPtr, bool drawInspector, float aChangeAmount, T _min, T _max)
		: AbstractSerializedVariable(aName, aCompPtr, drawInspector, aChangeAmount), myMin(_min), myMax(_max), hasMinMax(true)
	{

	}

	template<typename T>
	inline SerializedVariable<T>::SerializedVariable(const char* aName, Component* aCompPtr, bool drawInspector, float aChangeAmount, T aDefaultValue)
		: AbstractSerializedVariable(aName, aCompPtr, drawInspector, aChangeAmount), data(aDefaultValue)
	{

	}

	template<typename T>
	inline SerializedVariable<T>::SerializedVariable(const char* aName, Component* aCompPtr, bool drawInspector, float aChangeAmount, T aDefaultValue, T _min, T _max)
		: AbstractSerializedVariable(aName, aCompPtr, drawInspector, aChangeAmount), data(aDefaultValue), myMin(_min), myMax(_max), hasMinMax(true)
	{

	}

	template<typename T>
	concept HasGetType = requires(T type) { type.GetType(); };


	inline bool AbstractSerializedVariable::IsValid() const
	{
		return hasData;
	}

	template<typename T>
	inline T* SerializedVariable<T>::GetHandle()
	{
		return &data;
	}

	template<typename T>
	inline void* SerializedVariable<T>::GetRawData()
	{
		return &data;
	}

	template<typename T>
	inline void* SerializedVariable<T>::GetData()
	{
		if constexpr (Is_Array<T>::value)
			return &data[0];

		else if constexpr (Is_Vector<T>::value)
			return &data[0];

		else
			return &data;
	}

	template<typename T>
	inline const void* SerializedVariable<T>::GetData() const
	{
		if constexpr (Is_Array<T>::value)
			return &data[0];

		else if constexpr (Is_Vector<T>::value)
			return &data[0];

		else
			return &data;
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

		else if constexpr (std::is_same<T, Assets::Material>::value)
		{
			type = SerializedType_Material;
			sizePerElement = sizeof(Assets::Material);
		}
		else if constexpr (std::is_same<T, Assets::AudioClip>::value)
		{
			type = SerializedType_AudioClip;
			sizePerElement = sizeof(Assets::AudioClip);
		}
		else if constexpr (std::is_same<T, Assets::Texture>::value)
		{
			type = SerializedType_Texture;
			sizePerElement = sizeof(Assets::Texture);
		}
		else if constexpr (std::is_same<T, Assets::Prefab>::value)
		{
			type = SerializedType_Prefab;
			sizePerElement = sizeof(Assets::Prefab);
		}
		else if constexpr (std::is_same<T, Assets::Font>::value)
		{
			type = SerializedType_Font;
			sizePerElement = sizeof(Assets::Font);
		}

		else if constexpr (std::is_same<T, Math::Color>::value)
		{
			type = SerializedType_Color;
			sizePerElement = sizeof(T);
		}
		
		else if constexpr (std::is_same<T, bool>::value)
		{
			type = SerializedType_Bool;
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

		//else if constexpr (std::is_base_of<SerializedEnum, T>::value)
		//{
		//	type = SerializedType_Enum;
		//	sizePerElement = sizeof(T::e);
		//}

		else
		{

		}
	}

	template<typename T>
	inline void SerializedVariable<T>::Resize(const size_t& size)
	{
		if constexpr (Is_Vector<T>::value) data.resize(size);
	}


	//#ifdef ECL_EDITOR
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
}