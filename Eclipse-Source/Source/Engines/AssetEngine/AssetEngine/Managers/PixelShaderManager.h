#pragma once

#include "AssetEngine/Managers/AssetManager.h"

#include "AssetEngine/Assets/PixelShader.h"


namespace Eclipse::Assets
{
	class PixelShaderManager final : public AssetManager<class PixelShaders, class Assets::ShaderHandle>
	{
	public:
		PixelShaders Get(const size_t& id) override;

		PixelShaders GetDefault();

	protected:
		PixelShaders Load(const size_t& id) override;
		PixelShaders ConstructAsset(const size_t& id) override;
	};
}