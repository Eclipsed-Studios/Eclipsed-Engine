#include "SceneLoader.h"

#include "rapidjson/rapidjson/document.h"
#include "rapidjson/rapidjson/writer.h"
#include "rapidjson/rapidjson/stringbuffer.h"
#include "rapidjson/rapidjson/filewritestream.h"
#include "rapidjson/rapidjson/prettywriter.h"

#include <fstream>

#include "Utilities/Reflection/Reflection.h"
#include "Utilities/Reflection/SerializedVariable.h"

#include "Utilities/ChatGPT_Dump/Base64.hpp"

#include "Components/Base/Component.h"

#include "GraphicsEngine/RenderCommands/CommandList.h"

#include "PhysicsEngine/PhysicsEngine.h"

namespace Eclipse
{
	void SceneLoader::Save(const char* aPath)
	{
		rapidjson::Document d;
		d.SetObject();

		rapidjson::Document::AllocatorType& alloc = d.GetAllocator();

		std::unordered_map<std::string, std::unordered_map<unsigned, rapidjson::Value>> components;

		for (Component* pComp : ComponentManager::myComponents)
		{
			std::string compName = pComp->GetComponentName();

			if (compName == "Component")
			{
				continue;
			}
			rapidjson::Value value(rapidjson::kObjectType);

			value.AddMember("owner", pComp->gameObject->GetID(), alloc);
			value.AddMember("id", pComp->myInstanceComponentID, alloc);

			components[compName][pComp->myInstanceComponentID] = value;
		}


		auto& list = Reflection::ReflectionManager::GetList();
		for (auto& [pComp, varList] : list)
		{
			for (auto& var : varList)
			{
				std::string compName = var->GetComponent()->GetComponentName();
				Component* pComp = var->GetComponent();
				rapidjson::Value& val = components[compName][pComp->myInstanceComponentID];

				WriteMember(val, var, alloc);
			}
		}

		for (auto& [name, list] : components)
		{
			rapidjson::Value compArray(rapidjson::kArrayType);
			for (auto& [id, compJson] : list)
			{
				compArray.PushBack(compJson, alloc);
			}

			rapidjson::Value nameKey = rapidjson::Value(name.c_str(), alloc);
			d.AddMember(nameKey.Move(), compArray.Move(), alloc);
		}

		rapidjson::Value goArray(rapidjson::kArrayType);
		for (auto& [id, gameobject] : ComponentManager::myEntityIdToEntity)
		{
			rapidjson::Value goObj(rapidjson::kObjectType);
			goObj.AddMember("id", id, alloc);
			goObj.AddMember("name", rapidjson::Value(gameobject->GetName().c_str(), alloc).Move(), alloc);
			goArray.PushBack(goObj, alloc);
		}
		d.AddMember("GameObjects", goArray, alloc);

		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

		d.Accept(writer);

		std::ofstream ofs(aPath);
		ofs << buffer.GetString();
		ofs.close();
	}

	void SceneLoader::WriteMember(rapidjson::Value& aValue, Reflection::AbstractSerializedVariable* aSerialized, rapidjson::Document::AllocatorType& alloc)
	{
		using namespace rapidjson;

		aSerialized->ResolveTypeInfo();

		Value key(aSerialized->GetName(), alloc);
		Value jsonVal(kObjectType);

		if (aSerialized->GetType() == Reflection::AbstractSerializedVariable::SerializedType_String)
		{
			void* rawPtr = aSerialized->GetData();
			std::string* strPtr = static_cast<std::string*>(rawPtr);
			std::string& encoded = *strPtr;
			jsonVal.SetString(encoded.c_str(), alloc);
		}


		else if (aSerialized->GetType() == Reflection::AbstractSerializedVariable::SerializedType_List)
		{
			jsonVal.AddMember("size", aSerialized->GetCount(), alloc);

			void* rawPtr = aSerialized->GetData();
			std::string encoded = Base64::Encode(aSerialized->GetData(), aSerialized->GetSizeInBytes());
			jsonVal.AddMember("data", Value(encoded.c_str(), alloc).Move(), alloc);
		}



		else
		{
			int i = aSerialized->GetSizeInBytes();
			std::string encoded = Base64::Encode(aSerialized->GetData(), i);
			jsonVal.SetString(encoded.c_str(), alloc);
		}

		aValue.AddMember(key, jsonVal.Move(), alloc);
	}

	void SceneLoader::Load(const char* aPath)
	{
		using namespace rapidjson;

		CommandListManager::ResetAllCommandLists();

		ComponentManager::Clear();
		Reflection::ReflectionManager::ClearList();

		PhysicsEngine::CleanUp();
		PhysicsEngine::InitWorld();

		std::ifstream ifs(aPath);
		if (!ifs.is_open()) {
			return;
		}

		std::string jsonString((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>());

		ifs.close();

		Document d;
		if(d.Parse(jsonString.c_str()).HasParseError()) return;

		if (!d.HasMember("GameObjects")) return;

		const Value& objs = d["GameObjects"];
		{
			for (const Value& obj : objs.GetArray())
			{
				unsigned int id = obj["id"].GetUint();
				std::string name = obj["name"].GetString();

				GameObject* gObj = ComponentManager::CreateGameObjectNoTransformWithID(id);
				gObj->SetName(name);
			}
		}

		for (auto it = d.MemberBegin(); it != d.MemberEnd();)
		{
			if (it->name != "GameObjects")
			{
				LoadComponent(it->name.GetString(), it->value);
			}

			it++;
		}

		ComponentManager::OnLoadScene();
		
		// only if the game has started
		//ComponentManager::AwakeStartComponents();
	}

	void SceneLoader::LoadComponent(const std::string& componentName, const rapidjson::Value& aValue)
	{
		using namespace rapidjson;
		auto addComponent = ComponentRegistry::GetAddComponent(componentName);

		std::unordered_map<unsigned, Component*> compMap;
		for (const Value& val : aValue.GetArray())
		{
			const unsigned id = val["id"].GetUint();
			const unsigned owner = val["owner"].GetUint();

			compMap.emplace(id, addComponent(owner, id));
		}

		for (const Value& val : aValue.GetArray())
		{
			const unsigned id = val["id"].GetUint();
			auto& list = Reflection::ReflectionManager::GetList();

			Component* pComp = compMap[id];
			auto& varList = list[pComp];

			for (auto* var : varList)
			{
				if (pComp->myInstanceComponentID == id) LoadType(var, val);
			}
		}

		for (auto& [id, comp] : compMap)
		{
			comp->OnComponentAdded();
		}
	}
	void SceneLoader::LoadType(Reflection::AbstractSerializedVariable* aSERIALIZED_FIELDiable, const rapidjson::Value& aValue)
	{
		using namespace rapidjson;
		aSERIALIZED_FIELDiable->ResolveTypeInfo();

		if (!aValue.HasMember(aSERIALIZED_FIELDiable->GetName()))
			return;

		const Value& val = aValue[aSERIALIZED_FIELDiable->GetName()];

		if (aSERIALIZED_FIELDiable->GetType() == Reflection::AbstractSerializedVariable::SerializedType_String)
		{
			std::string strVal = val.GetString();

			std::string* str = (std::string*)aSERIALIZED_FIELDiable->GetData();
			str->resize(strVal.size());

			memcpy(str->data(), strVal.data(), strVal.size());
		}
		else if (aSERIALIZED_FIELDiable->GetType() == Reflection::AbstractSerializedVariable::SerializedType_List)
		{
			const unsigned count = val["size"].GetUint();
			aSERIALIZED_FIELDiable->Resize(count);

			const std::string strVal = val["data"].GetString();

			std::vector<unsigned char> decoded = Base64::Decode(strVal);
			memcpy(aSERIALIZED_FIELDiable->GetData(), decoded.data(), decoded.size());
		}
		else
		{
			std::string strVal = val.GetString();
			std::vector<unsigned char> decoded = Base64::Decode(strVal);
			memcpy(aSERIALIZED_FIELDiable->GetData(), decoded.data(), decoded.size());
		}
	}
}