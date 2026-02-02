#pragma once

#include "AssetEngine/AssetBinaryLoader/TypeLoaders/TypeLoader.h"
#include "AssetEngine/Models/AssetDatas/Handles/PrefabHandle.h"


namespace Eclipse::Assets
{
	class PrefabLoader : public TypeLoader<PrefabHandle>
	{
	public:
		PrefabHandle* Load(const size_t& id) override;
		void Load(const size_t& id, PrefabHandle* handle) override;
	};
}