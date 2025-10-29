#include "Texture.h"

#include <glad/glad.h>
#include "AssetEngine/Models/AssetDatas/Handles/TextureHandle.h"

namespace Eclipse
{
	ASSET_OPERATORS_IMPL(Textures, Assets::TextureHandle)

	int Textures::GetWidth() const
	{
		return dataHandle->width;
	}

	int Textures::GetHeight() const
	{
		return dataHandle->height;
	}

	float Textures::GetAspectRatio() const
	{
		return (float)dataHandle->width / (float)dataHandle->height;
	}

	size_t Textures::GetAssetID() const
	{
		return dataHandle->assetID;
	}

	void Textures::Bind(int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, dataHandle->textureID);
	}

	void Textures::Unbind(int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}