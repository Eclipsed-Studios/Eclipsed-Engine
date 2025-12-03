#include "PixelShaderLoader.h"

#include <filesystem>
#include "AssetEngine/AssetRegistry.h"
#include "CoreEngine/PathManager.h"

#include "AssetEngine/ShaderCompiler.h"


namespace Eclipse::Assets
{
	ShaderHandle* PixelShaderLoader::Load(const size_t& id)
	{
		ShaderHandle* handle = new ShaderHandle;

		Load(id, handle);
		return handle;
	}

	void PixelShaderLoader::Load(const size_t& id, ShaderHandle* handle)
	{
		auto& entry = AssetRegistry::GetInstance().GetRegisteredAsset(id);

		handle->assetID = id;
		ShaderCompiler::CompileShaderFromFile(entry.path.generic_string().c_str(), handle->shaderID, ShaderType::FRAGMENT_SHADER);
	}}