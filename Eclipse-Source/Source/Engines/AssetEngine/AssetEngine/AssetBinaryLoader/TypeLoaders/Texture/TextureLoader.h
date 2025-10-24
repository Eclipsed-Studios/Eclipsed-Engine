#pragma once

#include "AssetEngine/AssetBinaryLoader/TypeLoaders/TypeLoader.h"
#include "AssetEngine/Models/AssetDatas/Handles/TextureHandle.h"


namespace Eclipse::Assets
{
	class TextureLoader : public TypeLoader<TextureHandle>
	{
	public:
		TextureHandle* Load(const size_t& id) override;
	};
}