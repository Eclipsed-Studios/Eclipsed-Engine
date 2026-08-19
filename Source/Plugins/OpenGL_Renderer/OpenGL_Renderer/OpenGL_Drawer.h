#pragma once

#include "EclipsedEngine/Graphics/IDrawer.h"

namespace Eclipse::Graphics::OpenGL
{
	class OpenGL_Drawer : public IDrawer
	{
	public:
		void DrawSprite() override;
		void DrawTextSprite() override;
	};
}