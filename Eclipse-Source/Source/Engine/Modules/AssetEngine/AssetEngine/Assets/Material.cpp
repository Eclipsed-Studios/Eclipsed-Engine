#include "Material.h"
#include "AssetEngine/Models/AssetDatas/Handles/MaterialHandle.h"

#include "AssetEngine/Assets/Texture.h"

namespace Eclipse
{
	ASSET_OPERATORS_IMPL(Material, Assets::MaterialHandle);


	Texture& Material::GetTexture()
	{
		return dataHandle->texture;
	}
	const Texture& Material::GetTexture() const
	{
		return dataHandle->texture;
	}

	VertexShader& Material::GetVertexShader()
	{
		return dataHandle->vs;
	}
	const VertexShader& Material::GetVertexShader() const
	{
		return dataHandle->vs;
	}

	PixelShader& Material::GetPixelShader()
	{
		return dataHandle->ps;
	}

	const PixelShader& Material::GetPixelShader() const
	{
		return dataHandle->ps;
	}

	unsigned Material::GetShaderProgramID() const
	{
		return dataHandle->programID;
	}

	void Material::BindTexture()
	{
		dataHandle->texture.Bind();
	}

	void Material::BindShader()
	{
		glUseProgram(dataHandle->programID);
	}

	void Material::BindColor()
	{

		Math::Vector4f col = dataHandle->color.ToVector();
		
		GLuint location = glGetUniformLocation(dataHandle->programID, "material.color");
		glUniform4f(location, col.x, col.x, col.x, col.x);
	}

	void Material::Use()
	{
		BindShader();
		BindTexture();
		BindColor();
	}

	void Material::Create()
	{
		dataHandle->programID = glCreateProgram();
		glAttachShader(dataHandle->programID, dataHandle->vs.GetProgramID());
		glAttachShader(dataHandle->programID, dataHandle->ps.GetProgramID());
		glLinkProgram(dataHandle->programID);
	}
}