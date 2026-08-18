#include "OpenGL_Drawer.h"

#include "EclipsedEngine/Graphics/Sprite.h"

#include "OpenGL/glad/glad.h"

namespace Eclipse::Graphics::OpenGL
{
	void OpenGL_Drawer::DrawSprite(const Sprite& sprite)
	{
		glBindVertexArray(sprite.GetSpriteBufferID());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void OpenGL_Drawer::DrawTextSprite(const TextSprite& sprite)
	{
		glBindVertexArray(sprite.GetSpriteBufferID());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}