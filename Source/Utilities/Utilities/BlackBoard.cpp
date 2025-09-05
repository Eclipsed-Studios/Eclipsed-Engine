#include "BlackBoard.h"

#include <fstream>

using namespace rapidjson;

namespace ENGINE_NAMESPACE::Utilities
{
	rapidjson::Value BlackBoard::Save(rapidjson::Document::AllocatorType& allocator) const
	{
		Value obj(kObjectType);

		for (auto& [type, list] : myData)
		{
			Value objectList (kArrayType);
			for (auto& [name, bbValue] : list)
			{
				const Serializer& serializer = mySerializers.at(type);
				rapidjson::Value serializedValue = serializer(bbValue.value, allocator);

				Value entry(kObjectType);
				entry.AddMember(
					Value("name", allocator).Move(),
					Value(name.c_str(), allocator).Move(),
					allocator
				);
				entry.AddMember(
					Value("value", allocator).Move(),
					serializer(bbValue.value, allocator),
					allocator
				);
				objectList.PushBack(entry, allocator);
			}

			obj.AddMember(
				Value(type.name(), allocator).Move(),
				objectList,
				allocator
			);
		}

		return obj;
	}

	void BlackBoard::Load(const rapidjson::Value& aValue)
	{
		using namespace rapidjson;

		std::ifstream ifs(SETTINGS_PATH "settings.json");
		if (!ifs.is_open()) {
			//Save();
			return;
		}

		std::string jsonString((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>());

		ifs.close();

		Document d;
		if (d.Parse(jsonString.c_str()).HasParseError()) return;
	}
}