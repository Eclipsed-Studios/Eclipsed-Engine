#include "Settings.h"

#include "rapidjson/writer.h"

namespace Eclipse
{
	Settings::Settings(const char* aPath)
	{
		using namespace rapidjson;

		mySettingsPath = aPath;

		myJsonDoc.SetObject();

		std::ifstream ifs(mySettingsPath);
		if (!ifs.is_open()) {
			return;
		}

		std::string jsonString((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>());

		ifs.close();

		if (myJsonDoc.Parse(jsonString.c_str()).HasParseError())
		{
			myJsonDoc.SetObject();
		}
	}

	Settings::~Settings()
	{
		using namespace rapidjson;

		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		myJsonDoc.Accept(writer);

		std::ofstream ofs(mySettingsPath);
		ofs << buffer.GetString();
		ofs.close();
	}

	rapidjson::Value& Settings::Get(const char* aSettingName)
	{
		rapidjson::Document::AllocatorType& alloc = myJsonDoc.GetAllocator();

		if (!myJsonDoc.HasMember(aSettingName))
		{
			myJsonDoc.AddMember(rapidjson::Value(aSettingName, alloc), rapidjson::Value().Move(), alloc);
		}

		return myJsonDoc[aSettingName];
	}
}