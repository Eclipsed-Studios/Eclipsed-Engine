#include "SceneLoader.h"

#include "rapidjson/rapidjson/document.h"
#include "rapidjson/rapidjson/writer.h"
#include "rapidjson/rapidjson/stringbuffer.h"
#include "rapidjson/rapidjson/filewritestream.h"
#include "rapidjson/rapidjson/prettywriter.h"

#include <fstream>

namespace ENGINE_NAMESPACE
{
	void SceneLoader::Save(const char* aPath, Scene& outScene)
	{
		rapidjson::Document d;
		d.SetObject();

		rapidjson::Document::AllocatorType& alloc = d.GetAllocator();

		rapidjson::Value components(rapidjson::kArrayType);
		for (const Component* component : ComponentManager::GetComponents())
		{
			components.PushBack(component->Save(alloc), alloc);
		}

		d.AddMember("components", components, alloc);

		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		d.Accept(writer);

		std::ofstream ofs(ASSET_PATH"scene.json");
		ofs << buffer.GetString();
		ofs.close();
	}
}