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
				std::string compName = pComp->GetComponentName();

				for (auto& var : varList)
				{
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
			rapidjson::Value idVal(std::to_string(id).c_str(), alloc);
			goObj.AddMember("id", idVal, alloc);
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

		if (aReflectedVariable->GetTypeName() == "float")
		{
			jsonVal = *static_cast<float*>(aReflectedVariable->GetData());
		}
		else if (aReflectedVariable->GetTypeName() == "int")
		{
			jsonVal = *static_cast<int*>(aReflectedVariable->GetData());
		}
		else if (aReflectedVariable->GetTypeName() == "Math::Vector2<float>" || aReflectedVariable->GetTypeName() == "Math::Vector2f")
		{
			jsonVal = static_cast<Math::Vector2f*>(aReflectedVariable->GetData())->Save(alloc);
			WriteType(jsonVal, aReflectedVariable, alloc);
		}
		else if (aReflectedVariable->GetTypeName() == "Math::Vector2<unsigned>" || aReflectedVariable->GetTypeName() == "Math::Vector2ui"
			|| aReflectedVariable->GetTypeName() == "Math::Vector2<unsigned int>")
		{
			jsonVal = static_cast<Math::Vector2ui*>(aReflectedVariable->GetData())->Save(alloc);
			WriteType(jsonVal, aReflectedVariable, alloc);
		}
		else if (aReflectedVariable->GetTypeName() == "Math::Vector2<int>" || aReflectedVariable->GetTypeName() == "Math::Vector2i")
		{
			jsonVal = static_cast<Math::Vector2i*>(aReflectedVariable->GetData())->Save(alloc);
			WriteType(jsonVal, aReflectedVariable, alloc);
		}
		else if (aReflectedVariable->GetTypeName() == "Math::Vector2<double>" || aReflectedVariable->GetTypeName() == "Math::Vector2d")
		{
			jsonVal = static_cast<Math::Vector2d*>(aReflectedVariable->GetData())->Save(alloc);
			WriteType(jsonVal, aReflectedVariable, alloc);
		}

		else if (aReflectedVariable->GetTypeName() == "bool")
		{
			jsonVal = *static_cast<bool*>(aReflectedVariable->GetData());
		}
		else if (aReflectedVariable->GetTypeName() == "std::string")
		{
			std::string val = *static_cast<std::string*>(aReflectedVariable->GetData());
			jsonVal = Value(val.c_str(), static_cast<SizeType>(val.length()), alloc).Move();
		}
#ifdef _EDITOR
		else
		{
			auto& var = aReflectedVariable;
			DebugLogger::LogWarning("Reflected variable not supported in SceneLoading: " +
				std::string(var->GetComponent()->GetComponentName()) +
				" | " + var->GetTypeName() + " | " + var->GetName());
		}
#endif


		aValue.AddMember(key, jsonVal.Move(), alloc);

	}
	void SceneLoader::WriteType(rapidjson::Value& aValue, AbstractReflectedVariable* aReflectedVariable, rapidjson::Document::AllocatorType& alloc)
	{
		using namespace rapidjson;

		std::string val = aReflectedVariable->GetTypeName();
		Value typeKey("type", alloc);
		Value type(val.c_str(), static_cast<SizeType>(val.length()), alloc);
		aValue.AddMember(typeKey.Move(), type.Move(), alloc);
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

		for (const Value& val : aValue.GetArray())
		{
			addComponent(val["owner"].GetUint(), val["id"].GetUint());
		}
	}
}