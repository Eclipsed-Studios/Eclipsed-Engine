#include "IRenderer.h"

namespace Eclipse::Graphics
{
	IGraphicsBuffer* IRenderer::GetGraphicsBuffer()
	{
		return graphicsBuffer;
	}

	UniformVariableManager* IRenderer::GetUniformVariableManager()
	{
		return uniformVariableManager;
	}

	IDrawer* IRenderer::GetDrawer()
	{
		return drawer;
	}
}
