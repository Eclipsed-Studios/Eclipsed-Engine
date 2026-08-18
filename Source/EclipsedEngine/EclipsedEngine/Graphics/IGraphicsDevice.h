#pragma once

#include "EclipsedEngine.Core.hpp"
#include <unordered_map>
#include "EclipsedEngine/Graphics/Sprite.h"
#include "EclipsedEngine/Graphics/TextSprite.h"

namespace Eclipse::Graphics
{
	class ECL_API IGraphicsDevice 
	{
	public:
		virtual Sprite* CreateSprite() = 0;
		virtual TextSprite* CreateTextSprite() = 0;
	};
}