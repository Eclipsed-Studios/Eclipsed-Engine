#include "Texture.h"

#include <glad/glad.h>
#include "AssetEngine/Models/AssetDatas/Handles/TextureHandle.h"

namespace Eclipse
{
	ASSET_OPERATORS_IMPL(Texture, Assets::TextureHandle)

	int Texture::GetWidth() const
	{
		return dataHandle->width;
	}

	int Texture::GetHeight() const
	{
		return dataHandle->height;
	}

	float Texture::GetAspectRatio() const
	{
		return (float)dataHandle->width / (float)dataHandle->height;
	}

	size_t Texture::GetAssetID() const
	{
		return dataHandle->assetID;
	}

	unsigned Texture::GetTextureID() const
	{
		return dataHandle->textureID;
	}

	const Math::Vector2f& Texture::GetTextureSizeNormilized() const
	{
		return dataHandle->sizeNormalized;
	}

	float Texture::GetDimDivOne() const
	{
		return dataHandle->dimDivOne;
	}


	void Texture::Bind(int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, dataHandle->textureID);
	}

	void Texture::Unbind(int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}