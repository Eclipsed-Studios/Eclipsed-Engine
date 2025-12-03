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

#include "AssetEngine/ShaderCompiler.h"

namespace Eclipse::Assets
{
	ShaderHandle* VertexShaderLoader::Load(const size_t& id)
	{
		ShaderHandle* handle = new ShaderHandle;

		Load(id, handle);
		return handle;
	}
	void VertexShaderLoader::Load(const size_t& id, ShaderHandle* handle)
	{
		auto& entry = AssetRegistry::GetInstance().GetRegisteredAsset(id);
		handle->assetID = id;
		ShaderCompiler::CompileShaderFromFile(entry.path.generic_string().c_str(), handle->shaderID, ShaderType::VERTEX_SHADER);
	}		
}
