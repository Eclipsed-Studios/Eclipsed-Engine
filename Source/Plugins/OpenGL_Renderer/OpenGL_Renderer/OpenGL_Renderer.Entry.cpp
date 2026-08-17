#include "OpenGL_Renderer.Entry.h"

#include "OpenGL_Renderer.h"

#include "EclipsedEngine/AssetManager/Importers/AssetImporterRegistry.h"
#include "Texture/OpenGL_TextureImporter.h"

using namespace Eclipse::Graphics;
using namespace Eclipse::Assets;
using namespace Eclipse::Graphics::OpenGL;

OPENGL_RENDERER_API IRenderer* CreateRenderer()
{
	AssetImporterRegistry::Register(AssetType::Texture, new OpenGL::Assets::OpenGL_TextureImporter);

	return new OpenGL_Renderer;
}

OPENGL_RENDERER_API void DestroyRenderer(IRenderer* renderer)
{
	// Needs to be implemented.
}
