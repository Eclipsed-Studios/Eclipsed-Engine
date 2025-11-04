#include "Material.h"
#include "AssetEngine/Models/AssetDatas/Handles/MaterialHandle.h"

#include "AssetEngine/Assets/Texture.h"

#include "GraphicsEngine/OpenGL/OpenGLGraphicsAPI.h"

namespace Eclipse
{
	ASSET_OPERATORS_IMPL(Materials, Assets::MaterialHandle);

	size_t Materials::GetAssetID()const
	{
		return dataHandle->assetID;
	}


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

	void Materials::BindTexture()
	{
		dataHandle->texture.Bind();
	}

	void Materials::BindShader()
	{
		glUseProgram(dataHandle->programID);
	}

	void Materials::BindColor()
	{
		Math::Vector4f col = dataHandle->color.ToVector();
		GraphicsEngine::SetUniform(UniformType::Vector4f, dataHandle->programID, "material.color", &col);
	}

	void Materials::Use()
	{
		BindShader();
		BindTexture();
		BindColor();
	}

	void Materials::Create()
	{
		dataHandle->programID = glCreateProgram();
		glAttachShader(dataHandle->programID, dataHandle->vs.GetProgramID());
		glAttachShader(dataHandle->programID, dataHandle->ps.GetProgramID());
		glLinkProgram(dataHandle->programID);
	}
}