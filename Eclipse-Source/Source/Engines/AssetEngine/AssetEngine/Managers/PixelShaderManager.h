#pragma once

#include "AssetEngine/Managers/AssetManager.h"

#include "AssetEngine/Assets/Shader.h"


namespace Eclipse::Assets
{
	class PixelShaderManager final : public AssetManager<class Shaders, class Assets::ShaderHandle>
	{
	public:
		Shaders Get(const size_t& id) override;

	protected:
		Shaders Load(const size_t& id) override;
		Shaders ConstructAsset(const size_t& id) override;
	};
}