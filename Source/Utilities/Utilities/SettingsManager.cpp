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

		Value enginesValue = engineSettings.Save(allocator);
		d.AddMember(stringify(engineSettings), enginesValue, allocator);
		
		
		Value graphicsEnginesValue = graphicsSettings.Save(allocator);
		d.AddMember(stringify(graphicsSettings), graphicsEnginesValue, allocator);

		StringBuffer buffer;
		PrettyWriter<StringBuffer> writer(buffer);
		d.Accept(writer);

		std::ofstream ofs(SETTINGS_PATH "settings.json");
		ofs << buffer.GetString();
		ofs.close();
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
		d.Parse(jsonString.c_str());

		//engineSettings.Add<Math::Vector2i>("position", { -1, 3 });
		//engineSettings.Add<float>("length",  -9.34f);
		//engineSettings.Add<float>("other",  10.03f);
		//Save();

		if (d.HasMember(stringify(engineSettings)))
		{
			const Value& value = d[stringify(engineSettings)];
			engineSettings.Load(value);
		}

		if (d.HasMember(stringify(graphicsSettings)))
		{
			const Value& value = d[stringify(graphicsSettings)];
			graphicsSettings.Load(value);
		}
	}
}