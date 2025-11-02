#include "PixelShaderLoader.h"

#include <filesystem>
#include "AssetEngine/AssetRegistry.h"
#include "AssetEngine/PathManager.h"

#include "GraphicsEngine/ShaderCompiler.h"


namespace Eclipse::Assets
{
	ShaderHandle* PixelShaderLoader::Load(const size_t& id)
	{
		auto& entry = AssetRegistry::GetInstance().GetRegisteredAsset(id);

		ShaderHandle* handle = new ShaderHandle;
		handle->assetID = id;
		ShaderCompiler::CompileShaderFromFile(entry.path.generic_string().c_str(), handle->shaderID, ShaderType::FRAGMENT_SHADER);

		return handle;
	}
}