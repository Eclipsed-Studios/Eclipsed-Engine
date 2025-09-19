#include <AssetManagement/Loader/AssetLoader.hpp>

#include <AssetManagement/Resources/Shaders/PixelShader.h>
#include <AssetManagement/Resources/Shaders/Shader.h>
#include <AssetManagement/Resources/Shaders/VertexShader.h>

#include <ShaderCompiler.h>

namespace Eclipse
{
	template <>
	inline void AssetLoader::LoadFromPath(const char* aPath, PixelShader& outResource)
	{
		std::filesystem::path resolvedPath = aPath;
		if (resolvedPath.is_relative())
		{
			resolvedPath = std::filesystem::current_path().parent_path().generic_string() + "/" + resolvedPath.string();
		}
		else if (resolvedPath.is_absolute())
		{
			resolvedPath = aPath;
		}

		ShaderCompiler::CompileShaderFromFile(resolvedPath.string().c_str(), outResource.myPixelShaderID, ShaderType::FRAGMENT_SHADER);
	}

	template <>
	inline void AssetLoader::LoadFromPath(const char* aPath, VertexShader& outResource)
	{
		std::filesystem::path resolvedPath = aPath;
		if (resolvedPath.is_relative())
		{
			resolvedPath = std::filesystem::current_path().parent_path().generic_string() + "/" + resolvedPath.string();
		}
		else if (resolvedPath.is_absolute())
		{
			resolvedPath = aPath;
		}

		ShaderCompiler::CompileShaderFromFile(resolvedPath.string().c_str(), outResource.myVertexShaderID, ShaderType::VERTEX_SHADER);
	}
}