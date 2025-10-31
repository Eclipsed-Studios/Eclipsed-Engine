#include "Resources.h"

namespace Eclipse::Assets
{
	void Resourcess::Update()
	{
		textureManager.Update();
		materialManager.Update();
		vertexShaderManager.Update();
		pixelShaderManager.Update();
	}

	Textures Resourcess::GetDefaultTexture()
	{
		return textureManager.GetDefault();
	}
	VertexShaders Resourcess::GetDefaultVS()
	{
		return vertexShaderManager.GetDefault();
	}
	PixelShaders Resourcess::GetDefaultPS()
	{
		return pixelShaderManager.GetDefault();
	}
}