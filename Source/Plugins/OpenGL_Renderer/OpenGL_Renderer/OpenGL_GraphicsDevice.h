#pragma once

#include "EclipsedEngine/Graphics/IGraphicsDevice.h"

namespace Eclipse::Graphics::OpenGL
{
	class OpenGL_GraphicsDevice : public IGraphicsDevice
	{
	public:
		Sprite* CreateSprite() override;
		TextSprite* CreateTextSprite() override;

	};
}