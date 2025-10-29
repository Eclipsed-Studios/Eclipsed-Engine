#pragma once

#include "AssetEngine/AssetBinaryLoader/TypeLoaders/TypeLoader.h"
#include "AssetEngine/Models/AssetDatas/Handles/MaterialHandle.h"


namespace Eclipse::Assets
{
	class MaterialLoader : public TypeLoader<MaterialHandle>
	{
	public:
		MaterialHandle* Load(const size_t& id) override;
	};
}