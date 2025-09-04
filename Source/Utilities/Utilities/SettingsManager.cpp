#include "SettingsManager.h"

#include "rapidjson/rapidjson/document.h"
#include "rapidjson/rapidjson/writer.h"
#include "rapidjson/rapidjson/prettywriter.h"
#include "rapidjson/rapidjson/stringbuffer.h"
#include "rapidjson/rapidjson/filewritestream.h"

#include "defines.h"

#include <fstream>

namespace ENGINE_NAMESPACE
{
	void SettingsManager::Save()
	{
		using namespace rapidjson;

		Document d;
		d.SetObject();

		Document::AllocatorType& allocator = d.GetAllocator();

		Value enginesValue = settings.Save(allocator);
		d.AddMember(stringify(settings), enginesValue, allocator);

		StringBuffer buffer;
		PrettyWriter<StringBuffer> writer(buffer);
		d.Accept(writer);

		std::ofstream ofs(SETTINGS_PATH "settings.json");
		ofs << buffer.GetString();
		ofs.close();
	}

	Utilities::BlackBoard& SettingsManager::GetSettings()
	{
		return settings;
	}


	void SettingsManager::Load()
	{
		using namespace rapidjson;

		std::ifstream ifs(SETTINGS_PATH "settings.json");
		if (!ifs.is_open()) {
			Save();
		}

		std::string jsonString((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>());

		ifs.close();

		Document d;
		if (d.Parse(jsonString.c_str()).HasParseError()) return;

		if (d.HasMember(stringify(settings)))
		{
			const Value& value = d[stringify(settings)];
			settings.Load(value);
		}
	}
}