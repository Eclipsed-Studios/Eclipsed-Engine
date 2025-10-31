#pragma once

#include "AssetEngine/Managers/AssetManager.h"

#include "AssetEngine/Assets/VertexShader.h"


namespace Eclipse::Assets
{
	class VertexShaderManager final : public AssetManager<class VertexShaders, class Assets::ShaderHandle>
	{
	public:
		VertexShaders GetDefault();
		VertexShaders Get(const size_t& id) override;

	protected:
		VertexShaders Load(const size_t& id) override;
		VertexShaders ConstructAsset(const size_t& id) override;
	};
}