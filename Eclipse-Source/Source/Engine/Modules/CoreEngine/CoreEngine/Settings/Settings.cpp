#include "pch.h"

#include "EngineSettings.h"

#include "CoreEngine/PathManager.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

namespace Eclipse
{
	Settings::Settings(const char* path) : relPath(path)
	{
		std::ifstream ifs(PathManager::GetConfigDir() / relPath);
		if (!ifs.is_open()) {
			return;
		}

		std::string jsonString((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>());

		ifs.close();
		doc.Parse(jsonString.c_str());

		fileOpenend = true;
	}

	Settings::~Settings()
	{
		rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);

		std::ofstream ofs(PathManager::GetProjectRoot() / relPath);
		ofs << buffer.GetString();
		ofs.close();
	}
}