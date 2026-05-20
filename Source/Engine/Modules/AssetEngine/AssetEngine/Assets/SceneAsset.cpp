#include "TextureAsset.h"

namespace Eclipse::Assets
{
    Math::Vector2f Texture::GetDimDivOne() const
    {
        return dataPtr->dimDivOne;
    }

    Math::Vector2f Texture::GetSizeNormalized() const
    {
        return Math::Vector2f();
    }

    int Texture::GetWidth() const
    {
        return dataPtr->width;
    }

    int Texture::GetHeight() const
    {
        return dataPtr->height;
    }

    int Texture::GetChannels() const
    {
        return dataPtr->channels;
    }

    const std::vector<Math::RectSizePos> Texture::GetSpriteRects() const
    {
        return dataPtr->spriteRects;
    }





	float Texture::GetAspectRatio() const
	{
		return (float)dataPtr->width / (float)dataPtr->height;
	}

	unsigned Texture::GetTextureID() const
	{
		return dataPtr->textureID;
	}

	const Math::Vector2f& Texture::GetTextureSizeNormilized() const
	{
		return dataPtr->sizeNormalized;
	}

	void Texture::Bind(int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, dataPtr->textureID);
	}

	void Texture::Unbind(int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}