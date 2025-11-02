#include "VertexShaderLoader.h"
//#include "VertexShaderLoader.h"
//
//#include <filesystem>
//#include "AssetEngine/AssetImporter/TypeImporters/Texture/STB_ImporterStrategy.h"
//
//#include "AssetEngine/AssetCooker/CookedAsset.h"
#include "AssetEngine/AssetRegistry.h"
//#include "AssetEngine/PathManager.h"
//
//namespace Eclipse::Assets
//{
//	ShaderHandle* VertexShaderLoader::Load(const size_t& id)
//	{
//		return nullptr;
//	}
//}

#include "GraphicsEngine/ShaderCompiler.h"

namespace Eclipse::Assets
{
	ShaderHandle* VertexShaderLoader::Load(const size_t& id)
	{
		auto& entry = AssetRegistry::GetInstance().GetRegisteredAsset(id);

		ShaderHandle* handle = new ShaderHandle;
		handle->assetID = id;
		ShaderCompiler::CompileShaderFromFile(entry.path.generic_string().c_str(), handle->shaderID, ShaderType::VERTEX_SHADER);

		return handle;
	}
}
