#include "AssetMeta.h"

#include <string>

#include "rapidjson/allocators.h"
#include "rapidjson/document.h"

namespace Eclipse::Assets
{
	void AssetMeta::FromJson(const rapidjson::Value& obj)
    {
        if (obj.HasMember("type") && obj["type"].IsString())
            type = obj["type"].GetString();
    }
    void AssetMeta::ToJson(rapidjson::Value& obj, rapidjson::Document::AllocatorType& alloc) const
    {
        obj.SetObject();
        obj.AddMember("type", rapidjson::Value(type.c_str(), alloc), alloc);
    }
}
