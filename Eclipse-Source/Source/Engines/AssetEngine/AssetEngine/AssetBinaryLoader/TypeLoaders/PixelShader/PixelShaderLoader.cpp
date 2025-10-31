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
		ShaderCompiler::CompileShaderFromFile(entry.path.generic_string().c_str(), handle->shaderID, ShaderType::VERTEX_SHADER);

		return handle;
	}
}