#pragma once

#include <string>

#include "rapidjson/rapidjson/allocators.h"
#include "rapidjson/rapidjson/document.h"

namespace Eclipse::Assets
{
    struct AssetMeta {
    public:
        std::string type;

        virtual ~AssetMeta() = default;

        virtual void FromJson(const rapidjson::Value& obj);
        virtual void ToJson(rapidjson::Value& obj, rapidjson::Document::AllocatorType& alloc) const;
    };
}
