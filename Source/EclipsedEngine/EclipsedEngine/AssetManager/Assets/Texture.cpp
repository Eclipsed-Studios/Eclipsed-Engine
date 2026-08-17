#include "Texture.h"

namespace Eclipse::Assets
{
	int Texture::GetWidth() const
	{
		return data->width;
	}

	int Texture::GetHeight() const
	{
		return data->height;
	}

	int Texture::GetChannels() const
	{
		return data->channels;
	}

	Math::Vector2f Texture::GetInversedDimension() const
	{
		return data->invDimensions;
	}

	Math::Vector2f Texture::GetSizeNormalized() const
	{
		return data->sizeNormalized;
	}

	unsigned int Texture::GetTextureID() const
	{
		return data->textureID;
	}

	const std::vector<Math::RectSizePos>& Texture::GetSpriteRects() const
	{
		return data->spriteRects;
	}

	void Texture::Bind(unsigned slot) const
	{
		data->Bind(slot);
	}

	void Texture::Unbind(unsigned slot) const
	{
		data->Unbind(slot);
	}
}