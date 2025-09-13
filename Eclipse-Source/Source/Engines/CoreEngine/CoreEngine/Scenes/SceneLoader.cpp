#include "SceneLoader.h"

#include "rapidjson/rapidjson/document.h"
#include "rapidjson/rapidjson/writer.h"
#include "rapidjson/rapidjson/stringbuffer.h"
#include "rapidjson/rapidjson/filewritestream.h"
#include "rapidjson/rapidjson/prettywriter.h"

#include <fstream>

#include "Reflection/Reflection.h"
#include "Reflection/ReflectedVariable.h"

#include "DebugLogger.h"
#include "ChatGPT_Dump/Base64.hpp"

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
				DebugLogger::LogWarning("Component missing BASE_SELECTION macro.");
				continue;
			}
			rapidjson::Value value(rapidjson::kObjectType);

			value.AddMember("owner", pComp->gameObject->GetID(), alloc);
			value.AddMember("id", pComp->myComponentID, alloc);

			components[compName][pComp->myComponentID] = value;
		}


		auto& list = Reflection::GetList();
		for (auto& [pComp, typeToVarList] : list)
		{
			for (auto& [type, varList] : typeToVarList)
			{
				for (auto& var : varList)
				{
					std::string compName = var->GetComponent()->GetComponentName();
					Component* pComp = var->GetComponent();
					rapidjson::Value& val = components[compName][pComp->myComponentID];

					WriteMember(val, var, alloc);
				}
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

	void SceneLoader::WriteMember(rapidjson::Value& aValue, AbstractReflectedVariable* aReflectedVariable, rapidjson::Document::AllocatorType& alloc)
	{
		using namespace rapidjson;

		Value key(aReflectedVariable->GetName().c_str(), alloc);
		Value jsonVal(kObjectType);

		if (aReflectedVariable->GetTypeName() == "std::string")
		{
			void* rawPtr = aReflectedVariable->GetData();
			std::string* strPtr = static_cast<std::string*>(rawPtr);
			std::string& encoded = *strPtr; 
			jsonVal.SetString(encoded.c_str(), alloc);
		}
		else
		{
			std::string encoded = Base64::Encode(aReflectedVariable->GetData(), aReflectedVariable->GetSize());
			jsonVal.SetString(encoded.c_str(), alloc);
		}

		

		aValue.AddMember(key, jsonVal.Move(), alloc);
	}

	void SceneLoader::Load(const char* aPath)
	{
		using namespace rapidjson;

		std::ifstream ifs(aPath);
		if (!ifs.is_open()) {
			DebugLogger::LogError("Scene at path do not exist:   " + std::string(aPath));
			return;
		}

		std::string jsonString((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>());

		ifs.close();

		Document d;
		d.Parse(jsonString.c_str());


		Value gameobjectList;
		for (auto it = d.MemberBegin(); it != d.MemberEnd();)
		{
			if (it->name == "GameObjects")
			{
				gameobjectList = it->value.Move();
			}
			else
			{
				LoadComponent(it->name.GetString(), it->value);
			}

			it++;
		}
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

		ComponentManager::SortSHit();


		for (const Value& val : aValue.GetArray())
		{
			const unsigned id = val["id"].GetUint();
			auto& compIdToTypeList = Reflection::GetList();

			Component* pComp = compMap[id];
			auto& typeList = compIdToTypeList[pComp];

			for (auto& [type, varList] : typeList)
			{
				for (auto* var : varList)
				{
					LoadType(var, val);
				}
			}
		}
	}
	void SceneLoader::LoadType(AbstractReflectedVariable* aReflectedVariable, const rapidjson::Value& aValue)
	{
		std::string o(aValue[aReflectedVariable->GetName().c_str()].GetString());
		
		if (aReflectedVariable->GetTypeName() == "std::string")
		{
			std::string* str = (std::string*)aReflectedVariable->GetData();
			str->resize(o.size());

			memcpy(str->data(), o.data(), o.size());
		}
		else
		{
			std::vector<unsigned char> decoded = Base64::Decode(o);
			memcpy(aReflectedVariable->GetData(), decoded.data(), decoded.size());
		}
	}
}