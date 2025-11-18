#pragma once

#include "AssetEngine/Managers/AssetManager.h"

#include "AssetEngine/Assets/PixelShader.h"


namespace Eclipse::Assets
{
	class PixelShaderLoader;
	class PixelShaderManager final : public AssetManager<class PixelShader, class Assets::ShaderHandle>
	{
	public:
		PixelShader Get(const size_t& id) override;

		PixelShader GetDefault();

	protected:
		PixelShaderLoader& GetLoader();

		void Reload(const size_t& id) override;

		PixelShader Load(const size_t& id) override;
		PixelShader ConstructAsset(const size_t& id) override;
	};
}