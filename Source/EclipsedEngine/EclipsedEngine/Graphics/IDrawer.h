#pragma once

#include "EclipsedEngine/Graphics/Sprite.h"
#include "EclipsedEngine/Graphics/TextSprite.h"

#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"

namespace Eclipse::Graphics
{
	class IDrawer 
	{
	public:
		virtual void DrawSprite(SpriteRenderer2D* spriteRend, Transform2D* transform) = 0;
	};
}