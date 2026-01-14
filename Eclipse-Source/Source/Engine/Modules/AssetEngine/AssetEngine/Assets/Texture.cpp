#include "Texture.h"

#include <glad/glad.h>
#include "AssetEngine/Models/AssetDatas/Handles/TextureHandle.h"

namespace Eclipse
{
	ASSET_OPERATORS_IMPL(Texture, Assets::TextureHandle)

		const std::vector<Math::RectSizePos>& Texture::GetRects()
	{
		return dataHandle->rects;
	}

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

	unsigned Texture::GetTextureID() const
	{
		return dataHandle->textureID;
	}

	const Math::Vector2f& Texture::GetTextureSizeNormilized() const
	{
		return dataHandle->sizeNormalized;
	}

	Math::Vector2f Texture::GetDimDivOne() const
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