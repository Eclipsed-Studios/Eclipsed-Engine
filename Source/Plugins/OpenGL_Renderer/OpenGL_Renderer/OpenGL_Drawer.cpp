#include "OpenGL_Drawer.h"

#include "EclipsedEngine/Graphics/Sprite.h"
#include "EclipsedEngine/Assets/Assets/MaterialAsset.h"

#include "OpenGL/glad/glad.h"
#include "OpenGL_GraphicsDevice.h"
#include "EclipsedEngine/Graphics/RendererManager.h"
#include "EclipsedEngine/Graphics/IRenderer.h"

namespace Eclipse::Graphics::OpenGL
{
	//void OpenGL_Drawer::DrawSprite()
	//{
	//	//glBindVertexArray(sprite.GetSpriteBufferID());
	//	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//	//glBindVertexArray(0);
	//}

	//void OpenGL_Drawer::DrawTextSprite()
	//{
	//	//glBindVertexArray(sprite.GetSpriteBufferID());
	//	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//	//glBindVertexArray(0);
	//}

	void OpenGL_Drawer::DrawSprite(SpriteRenderer2D* spriteRend, Transform2D* transform)
	{
		//Assets::Material* mat = spriteRend->GetMaterial();
		//Graphics::IRenderer& r = Graphics::RendererManager::GetRenderer();
		//r.GetDevice()->BindMaterial(*mat);


	}
}