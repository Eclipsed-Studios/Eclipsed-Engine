#include "AbstractSerializedVariable.h"

#include "Reflection.h"

namespace Eclipse::Reflection
{
	AbstractSerializedVariable::~AbstractSerializedVariable()
	{
		ReflectionManager::UnregisterVariable(this);
	}

//#ifdef ECLIPSED_EDITOR
	AbstractSerializedVariable::AbstractSerializedVariable(const char* aName, Component* aCompPtr, bool drawInspector)
		: name(aName), pComponent(aCompPtr), canDrawInspector(drawInspector)
	{
		ReflectionManager::RegisterVariable(this);
	}

	std::string AbstractSerializedVariable::GetNameID() const { return std::string("##") + std::string(name); }
//#else 
//	AbstractSerializedVariable::AbstractSerializedVariable(const char* aName, Component* aCompPtr)
//		: name(aName), pComponent(aCompPtr)
//	{
//		ReflectionManager::RegisterVariable(this);
//	}
//#endif


	void AbstractSerializedVariable::DrawTest()
	{
		ResolveTypeInfo();
		ImGuiDataType iType = GetImGuiType();


		int size = 0;
		int elements = 1;
		//if(iType == ImGuiDataType_String) size = 


		size = sizes[iType];
		if (type == SerializedType_Custom_Type) elements = sizePerElement / size;

		ImGui::Text(GetName());

		switch (type)
		{
		case SerializedType_List:
		case SerializedType_Array:
		case SerializedType_Component:
		case SerializedType_Gameobject:
		case SerializedType_Enum:
			break;



		case SerializedType_String:
			ImGui::SameLine();

			char TemporaryName[256];
			std::strcpy(TemporaryName, static_cast<const char*>(GetData()));

			if (ImGui::InputText(("##" + std::to_string(iType) + GetName()).c_str(), TemporaryName, 256, ImGuiInputTextFlags_EnterReturnsTrue))
			{
				memcpy(GetData(), &TemporaryName, strlen(TemporaryName) + 1);
			}
			break;

		case SerializedType_Custom_Type:
		case SerializedType_Fundamental:
			ImGui::SameLine();

			ImGui::DragScalarN(("##" + std::to_string(iType) + GetName()).c_str(), iType, GetData(), elements);
			break;
		}
	}

	const char* AbstractSerializedVariable::GetName() const { return name; }
	Component* AbstractSerializedVariable::GetComponent() { return pComponent; }
	const Component* AbstractSerializedVariable::GetComponent() const { return pComponent; }
	unsigned AbstractSerializedVariable::GetSizePerElement() const { return sizePerElement; }
	unsigned AbstractSerializedVariable::GetSizeInBytes() const { return sizePerElement * count; }
	unsigned AbstractSerializedVariable::GetCount() const { return count; }
	AbstractSerializedVariable::SerializedTypes_ AbstractSerializedVariable::GetType() const { return type; }
}