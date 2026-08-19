#pragma once

#include "EclipsedEngine.Core.hpp"
#include <unordered_map>
#include "EclipsedEngine/Graphics/Sprite.h"
#include "EclipsedEngine/Graphics/TextSprite.h"

#include "EclipsedEngine/Assets/Assets/TextureAsset.h"
#include "EclipsedEngine/Assets/Assets/MaterialAsset.h"

namespace Eclipse::Graphics
{
	class ECL_API IGraphicsDevice 
	{
	public:
		virtual Sprite* CreateSprite() = 0;
		virtual TextSprite* CreateTextSprite() = 0;

	public:
		virtual void BindTexture(unsigned slot, Assets::Texture& texture) = 0;
		virtual void BindShader(unsigned id) = 0;
		virtual void BindMaterial(Assets::Material& material) = 0;
	};
}