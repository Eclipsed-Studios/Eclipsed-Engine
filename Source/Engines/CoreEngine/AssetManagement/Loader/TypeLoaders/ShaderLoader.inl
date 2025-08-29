#include <AssetManagement/Loader/AssetLoader.hpp>

#include <AssetManagement/Resources/Shaders/PixelShader.h>
#include <AssetManagement/Resources/Shaders/Shader.h>
#include <AssetManagement/Resources/Shaders/VertexShader.h>

#include <ShaderCompiler.h>


/*
		ShaderCompiler::CompileShaderFromFile(ASSET_PATH"Shaders/DefaultSpriteVertexShader.glsl", myVertexShader, ShaderType::VERTEX_SHADER);
		ShaderCompiler::CompileShaderFromFile(ASSET_PATH"Shaders/DefaultSpritePixelShader.glsl", myFragmentShader, ShaderType::FRAGMENT_SHADER);

		myShaderProgram = glCreateProgram();
		glAttachShader(myShaderProgram, myVertexShader);
		glAttachShader(myShaderProgram, myFragmentShader);
		glLinkProgram(myShaderProgram);
		*/

namespace ENGINE_NAMESPACE
{
	template <>
	inline void AssetLoader::LoadFromPath(const char* aPath, PixelShader& outResource)
	{
		std::string fullPath = std::string(ASSET_PATH) + aPath;
		ShaderCompiler::CompileShaderFromFile(aPath, outResource.myPixelShaderID, ShaderType::FRAGMENT_SHADER);
	}

	template <>
	inline void AssetLoader::LoadFromPath(const char* aPath, VertexShader& outResource)
	{
		std::string fullPath = std::string(ASSET_PATH) + aPath;
		ShaderCompiler::CompileShaderFromFile(aPath, outResource.myVertexShaderID, ShaderType::VERTEX_SHADER);
	}
}