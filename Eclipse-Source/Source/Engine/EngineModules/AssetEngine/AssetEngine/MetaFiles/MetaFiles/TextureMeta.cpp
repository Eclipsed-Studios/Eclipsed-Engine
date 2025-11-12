#include "TextureMeta.h"

namespace Eclipse::Assets
{
	void TextureMeta::FromJson(const rapidjson::Value& obj)
	{
		AssetMeta::FromJson(obj);
	}

	void TextureMeta::ToJson(rapidjson::Value& obj, rapidjson::Document::AllocatorType& alloc) const
	{
		AssetMeta::ToJson(obj, alloc);


	}
}