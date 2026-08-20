#include "AbstractSerializedVariable.h"

#include "Reflection.h"

#include "Assets/Assets/MaterialAsset.h"
#include "Assets/Assets/AudioAsset.h"
#include "Assets/Assets/TextureAsset.h"
#include "Assets/Assets/FontAsset.h"
#include "Assets/Assets/PrefabAsset.h"
#include "Assets/AssetManager.h"

#include "ReflectionTypeChecks.h"
#include "ECS/Component.h"

#include "Core/MainSingleton.h"
#include "Assets/Core/AssetDatabase.h"

namespace Eclipse::Reflection
{
	std::unordered_map<std::type_index, ImGuiDataType> AbstractSerializedVariable::types = {
		{typeid(char), ImGuiDataType_S8},
		{typeid(unsigned char), ImGuiDataType_U8},

		{typeid(short), ImGuiDataType_S16},
		{typeid(unsigned short), ImGuiDataType_U16},

		{typeid(int), ImGuiDataType_S32},
		{typeid(unsigned int), ImGuiDataType_U32},

		{typeid(long long), ImGuiDataType_S64},
		{typeid(unsigned long long), ImGuiDataType_U64},

		{typeid(float), ImGuiDataType_Float},
		{typeid(double), ImGuiDataType_Double},

		{typeid(bool), ImGuiDataType_Bool},

		{typeid(char*), ImGuiDataType_String},
		{typeid(const char*), ImGuiDataType_String},
		{typeid(std::string), ImGuiDataType_String},
	};
	
	std::unordered_map<ImGuiDataType, size_t> AbstractSerializedVariable::sizes = {
		{ImGuiDataType_S8, sizeof(char)},
		{ImGuiDataType_U8, sizeof(unsigned char)},

		{ImGuiDataType_S16, sizeof(short)},
		{ImGuiDataType_U16, sizeof(unsigned short)},

		{ImGuiDataType_S32, sizeof(int)},
		{ImGuiDataType_U32, sizeof(unsigned int)},

		{ImGuiDataType_S64, sizeof(long long)},
		{ImGuiDataType_U64, sizeof(unsigned long long)},

		{ImGuiDataType_Float, sizeof(float)},
		{ImGuiDataType_Double, sizeof(double)},

		{ImGuiDataType_Bool, sizeof(bool)},

		{ImGuiDataType_String, 20000},
	};

	
	AbstractSerializedVariable::~AbstractSerializedVariable()
	{
		ReflectionManager::UnregisterVariable(this);
	}

	//#ifdef ECL_EDITOR
	AbstractSerializedVariable::AbstractSerializedVariable(const char* aName, Component* aCompPtr, bool drawInspector, float aChangeAmount)
		: name(aName), pComponent(aCompPtr), canDrawInspector(drawInspector), myChangAmount(aChangeAmount)
	{
		ReflectionManager::RegisterVariable(this);
		imguiID = rand();
	}

	std::string AbstractSerializedVariable::GetNameID() const { return std::string("##") + std::string(name); }
	//#else 
	//	AbstractSerializedVariable::AbstractSerializedVariable(const char* aName, Component* aCompPtr)
	//		: name(aName), pComponent(aCompPtr)
	//	{
	//		ReflectionManager::RegisterVariable(this);
	//	}
	//#endif

	const char* AbstractSerializedVariable::GetName() const { return name; }
	Component* AbstractSerializedVariable::GetComponent() { return pComponent; }
	const Component* AbstractSerializedVariable::GetComponent() const { return pComponent; }
	unsigned AbstractSerializedVariable::GetSizePerElement() const { return sizePerElement; }
	unsigned AbstractSerializedVariable::GetSizeInBytes() const { return sizePerElement * count; }
	unsigned AbstractSerializedVariable::GetCount() const { return count; }
	AbstractSerializedVariable::SerializedTypes_ AbstractSerializedVariable::GetType() const { return type; }
}