#include "Resources.h"

namespace Eclipse::Assets
{
	void Resources::Update()
	{
		textureManager.Update();
		materialManager.Update();
		vertexShaderManager.Update();
		pixelShaderManager.Update();
	}

	Material Resources::GetDefaultMaterial()
	{
		return materialManager.GetDefault();
	}

	Texture Resources::GetDefaultTexture()
	{
		return textureManager.GetDefault();
	}
	VertexShader Resources::GetDefaultVS()
	{
		return vertexShaderManager.GetDefault();
	}
	PixelShader Resources::GetDefaultPS()
	{
		return pixelShaderManager.GetDefault();
	}
}