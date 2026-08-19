#pragma once

#include "EclipsedEngine/Graphics/Sprite.h"
#include "EclipsedEngine/Graphics/TextSprite.h"

namespace Eclipse::Graphics
{
	class IDrawer 
	{
	public:
		virtual void DrawSprite() = 0;
		virtual void DrawTextSprite() = 0;
	};
}