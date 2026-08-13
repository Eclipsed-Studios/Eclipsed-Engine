#pragma once

#include "EclipsedEngine.Core.hpp"
#include <unordered_map>

namespace Eclipse::Graphics
{
	class IRenderer;
	class ECL_API RendererManager final
	{
	public:
		static void LoadRenderer(const char* rendererPath);

	public:
		static IRenderer& GetRenderer();

	private:
		using CreateRendererFn = IRenderer * (*)();
		using DestroyRendererFn = void (*)(IRenderer*);

		static void* ActiveRendererDLL;
		static DestroyRendererFn DestroyRenderer;

		static IRenderer* ActiveRenderer;
	};
}