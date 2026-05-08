#include "MaterialAsset.h"

namespace Eclipse::Assets
{
	Texture Material::GetTexture() const
	{
		return dataPtr->texture;
	}

	PixelShader Material::GetPixelShader() const
	{
		return dataPtr->pixelShader;
	}

	VertexShader Material::GetVertexShader() const
	{
		return dataPtr->vertexShader;
	}

	void Material::BindTexture()
	{
		dataPtr->texture.Bind();
	}

	void Material::BindShader()
	{
		glUseProgram(dataPtr->programID);
	}

	void Material::BindColor()
	{
		materialBuffer.color = dataPtr->color;
	}

	void Material::Use()
	{
		BindShader();
		BindTexture();
		BindColor();
	}

	void Material::Create()
	{

	}
}