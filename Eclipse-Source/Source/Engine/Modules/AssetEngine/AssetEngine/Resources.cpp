#include "Resources.h"

namespace Eclipse::Assets
{
	TextureManager Resources::textureManager{};
	MaterialManager Resources::materialManager {};
	VertexShaderManager Resources::vertexShaderManager {};
	PixelShaderManager Resources::pixelShaderManager {};
	AudioClipManager Resources::audioClipManager {};

	void Resources::Update()
	{
		textureManager.Update();
		materialManager.Update();
		vertexShaderManager.Update();
		pixelShaderManager.Update();
		audioClipManager.Update();
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