#pragma once

#include "EclipsedEngine/Graphics/Sprite.h"
#include "EclipsedEngine/Graphics/TextSprite.h"

namespace Eclipse::Graphics
{
	class IDrawer 
	{
	public:
		virtual void DrawSprite(const Sprite& sprite) = 0;
		virtual void DrawTextSprite(const TextSprite& sprite) = 0;
	};
}