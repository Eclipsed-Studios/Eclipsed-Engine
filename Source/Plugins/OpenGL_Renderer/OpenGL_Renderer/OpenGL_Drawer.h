#pragma once

#include "EclipsedEngine/Graphics/IDrawer.h"

namespace Eclipse::Graphics::OpenGL
{
	class OpenGL_Drawer : public IDrawer
	{
	public:
		void DrawSprite(const Sprite& sprite) override;
		void DrawTextSprite(const TextSprite& sprite) override;
	};
}