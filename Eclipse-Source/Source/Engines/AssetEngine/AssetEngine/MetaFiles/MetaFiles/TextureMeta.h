#pragma once

#include "AssetMeta.h"
#include <string>
#include <vector>

#include "Utilities/Math/RectSizePos.h"

#include "rapidjson/rapidjson/allocators.h"
#include "rapidjson/rapidjson/document.h"

namespace Eclipse::Assets
{
    struct TextureMeta : public AssetMeta {
    public:
        std::vector<Math::RectSizePos> myRects;


        virtual ~TextureMeta() = default;

        void FromJson(const rapidjson::Value& obj) override;
        void ToJson(rapidjson::Value& obj, rapidjson::Document::AllocatorType& alloc) const override;
    };
}
