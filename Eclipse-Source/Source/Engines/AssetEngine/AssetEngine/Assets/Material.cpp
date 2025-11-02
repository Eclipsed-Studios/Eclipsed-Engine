#include "Material.h"
#include "AssetEngine/Models/AssetDatas/Handles/MaterialHandle.h"

#include "AssetEngine/Assets/Texture.h"

#include "GraphicsEngine/OpenGL/OpenGLGraphicsAPI.h"

namespace Eclipse
{
	ASSET_OPERATORS_IMPL(Materials, Assets::MaterialHandle);

	Textures& Materials::GetTexture()
	{
		return dataHandle->texture;
	}
	const Textures& Materials::GetTexture() const
	{
		return dataHandle->texture;
	}

	VertexShaders& Materials::GetVertexShader()
	{
		return dataHandle->vs;
	}
	const VertexShaders& Materials::GetVertexShader() const
	{
		return dataHandle->vs;
	}

	PixelShaders& Materials::GetPixelShader()
	{
		return dataHandle->ps;
	}

	const PixelShaders& Materials::GetPixelShader() const
	{
		return dataHandle->ps;
	}

	unsigned Materials::GetShaderProgramID() const
	{
		return dataHandle->programID;
	}


	void Materials::Use()
	{
		glUseProgram(dataHandle->programID);

		dataHandle->texture.Bind();

		Math::Vector4f col = dataHandle->color.ToVector();
		GraphicsEngine::SetUniform(UniformType::Vector4f, dataHandle->programID, "material.color", &col);
	}

	void Materials::Create()
	{
		dataHandle->programID = glCreateProgram();
		glAttachShader(dataHandle->programID, dataHandle->vs.GetProgramID());
		glAttachShader(dataHandle->programID, dataHandle->ps.GetProgramID());
		glLinkProgram(dataHandle->programID);
	}
}