#pragma once

#include "AssetEngine/Managers/AssetManager.h"

#include "AssetEngine/Assets/VertexShader.h"


namespace Eclipse::Assets
{
	class VertexShaderLoader;
	class VertexShaderManager final : public AssetManager<class VertexShader, class Assets::ShaderHandle>
	{
	public:
		VertexShader GetDefault();
		VertexShader Get(const size_t& id) override;

	protected:
		VertexShaderLoader& GetLoader();

		void Reload(const size_t& id) override;

		VertexShader Load(const size_t& id) override;
		VertexShader ConstructAsset(const size_t& id) override;
	};
}