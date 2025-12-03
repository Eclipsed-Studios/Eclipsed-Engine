#include "SpriteAnimationLoader.h"
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
namespace Eclipse::Assets
{
	SpriteAnimationHandle* SpriteAnimationLoader::Load(const size_t& id)
	{
		auto& entry = AssetRegistry::GetInstance().GetRegisteredAsset(id);

		SpriteAnimationHandle* handle = new SpriteAnimationHandle;
		handle->assetID = id;
		//ShaderCompiler::CompileShaderFromFile(entry.path.generic_string().c_str(), handle->shaderID, ShaderType::VERTEX_SHADER);

		return handle;
	}
}
