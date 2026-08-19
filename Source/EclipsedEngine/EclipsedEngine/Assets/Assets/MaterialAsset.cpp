#include "EclipsedEngine/Assets/Assets/MaterialAsset.h"

namespace Eclipse::Assets
{
	Texture& Material::GetTexture() const
	{
		return dataPtr->texture;
	}

	PixelShader& Material::GetPixelShader() const
	{
		return dataPtr->pixelShader;
	}

	VertexShader& Material::GetVertexShader() const
	{
		return dataPtr->vertexShader;
	}


	unsigned Material::GetProgramID() const
	{
		return dataPtr->programID;
	}

	MaterialBuffer& Material::GetBuffer()
	{
		return materialBuffer;
	}
}