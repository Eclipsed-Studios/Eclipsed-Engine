#pragma once

#include "AssetEngine/AssetBinaryLoader/TypeLoaders/TypeLoader.h"
#include "AssetEngine/Models/AssetDatas/Handles/TextureHandle.h"


namespace Eclipse::Assets
{
	class TextureLoader : public TypeLoader<TextureHandle>
	{
	public:
		TextureHandle* Load(const size_t& id) override;
		void Load(const size_t& id, TextureHandle* handle) override;

	private:
		bool MetaFileExists(const size_t& id);
		void LoadMetaFile(const size_t& id, TextureHandle* handle);

	};
}