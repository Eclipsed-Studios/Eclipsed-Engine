#include "MetaFileRegistry.h"

#include "rapidjson/rapidjson/prettywriter.h"
#include <fstream>

namespace Eclipse
{
	void MetaFileRegistry::Load()
	{
		using namespace rapidjson;

		myDocument.SetObject();

		std::ifstream ifs(ASSET_PATH "meta_data.meta");
		if (!ifs.is_open()) {
			return;
		}

		std::string jsonString((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>());

		ifs.close();

		myDocument.Parse(jsonString.c_str());
	}

	void MetaFileRegistry::Save()
	{
		using namespace rapidjson;

		StringBuffer buffer;
		PrettyWriter<StringBuffer> writer(buffer);
		myDocument.Accept(writer);

		std::ofstream ofs(ASSET_PATH "meta_data");
		ofs << buffer.GetString();
		ofs.close();
	}
}