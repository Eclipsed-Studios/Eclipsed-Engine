#include "AbstractSerializedVariable.h"

#include "Reflection.h"

#include "EclipsedEngine/Editor/Common/DragAndDrop.h"
#include "AssetEngine/Assets/Material.h"
#include "AssetEngine/Assets/AudioClip.h"
#include "AssetEngine/Assets/Texture.h"
#include "AssetEngine/Resources.h"

#include "ReflectionTypeChecks.h"
#include "EntityEngine/Component.h"

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

		bool drawDefualt = pComponent->DrawDefaultInspector();

		if (drawDefualt)
		{
			int size = 0;
			int elements = 1;
			//if(iType == ImGuiDataType_String) size = 


			size = sizes[iType];
			if (type == SerializedType_Custom_Type) elements = sizePerElement / size;

			ImVec2 startPos = ImGui::GetCursorPos();
			ImGui::Text(GetName());

			switch (type)
			{
			case SerializedType_Material:
			{
				ImGui::SameLine();

				std::string name = "No material.";

				Material* mat = (Material*)GetData();
				if (mat->IsValid())
				{
					name = Assets::AssetRegistry::GetInstance().GetRegisteredAsset(mat->GetAssetID()).path.filename().stem().string();
				}

				if (Editor::DragAndDrop::BeginTarget(name.c_str(), Utilities::FileInfo::FileType_Material))
				{
					*mat = Assets::Resources::Get<Material>(Editor::DragAndDrop::payloadBuffer);
				}
			} break;


			case SerializedType_AudioClip:
			{
				ImGui::SameLine();

				std::string name = "No audio clip.";

				AudioClip* clip = (AudioClip*)GetData();
				if (clip->IsValid())
				{
					name = Assets::AssetRegistry::GetInstance().GetRegisteredAsset(clip->GetAssetID()).path.filename().stem().string();
				}

				if (Editor::DragAndDrop::BeginTarget(name.c_str(), Utilities::FileInfo::FileType_Audio))
				{
					*clip = Assets::Resources::Get<AudioClip>(Editor::DragAndDrop::payloadBuffer);
				}
			} break;

			case SerializedType_Texture:
			{
				ImGui::SameLine();

				std::string name = "No texture.";

				Texture* texture = (Texture*)GetData();
				if (texture->IsValid())
				{
					name = Assets::AssetRegistry::GetInstance().GetRegisteredAsset(texture->GetAssetID()).path.filename().stem().string();
				}

				if (Editor::DragAndDrop::BeginTarget(name.c_str(), Utilities::FileInfo::FileType_Texture))
				{
					*texture = Assets::Resources::Get<Texture>(Editor::DragAndDrop::payloadBuffer);
				}
			} break;


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

			ImGui::SetCursorPosX(startPos.x);
		}

		if (pComponent->HasDrawInspector())
		{
			pComponent->OnDrawInspector();
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