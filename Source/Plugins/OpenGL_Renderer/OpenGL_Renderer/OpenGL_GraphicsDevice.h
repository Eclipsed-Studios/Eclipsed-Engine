#pragma once

#include "EclipsedEngine/Graphics/IGraphicsDevice.h"

namespace Eclipse::Graphics::OpenGL
{
	class OpenGL_GraphicsDevice : public IGraphicsDevice
	{
	public:
		Sprite* CreateSprite() override;
		TextSprite* CreateTextSprite() override;

	public:
		void BindTexture(unsigned slot, Assets::Texture& texture) override;
		void BindShader(unsigned id) override;
		void BindMaterial(Assets::Material& material) override;
	};
}