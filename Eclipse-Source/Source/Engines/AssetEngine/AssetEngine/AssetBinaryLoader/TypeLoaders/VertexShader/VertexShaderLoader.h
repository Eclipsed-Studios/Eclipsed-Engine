#pragma once

#include "AssetEngine/AssetBinaryLoader/TypeLoaders/TypeLoader.h"
#include "AssetEngine/Models/AssetDatas/Handles/ShaderHandle.h"


namespace Eclipse::Assets
{
	class VertexShaderLoader : public TypeLoader<ShaderHandle>
	{
	public:
		ShaderHandle* Load(const size_t& id) override;
		void Load(const size_t& id, ShaderHandle* handle) override;
	};
}