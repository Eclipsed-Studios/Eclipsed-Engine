#include "RendererManager.h"

#include <Windows.h>
#include <filesystem>

#include "IRenderer.h"

namespace Eclipse::Graphics
{
	void* RendererManager::ActiveRendererDLL;
	RendererManager::DestroyRendererFn RendererManager::DestroyRenderer;

	IRenderer* RendererManager::ActiveRenderer;

	void RendererManager::LoadRenderer(const char* rendererPath)
	{
		if (!std::filesystem::exists(rendererPath))
			return;

		void* renderer = LoadLibraryA(rendererPath);
		if (!renderer)
		{
			const DWORD error = GetLastError();
			printf("LoadLibraryA failed. Error code: %lu\n", error);

			return;
		}

		ActiveRendererDLL = renderer;

		void* createRendererFn = GetProcAddress((HMODULE)ActiveRendererDLL, "CreateRenderer");
		if (!createRendererFn)
		{
			FreeLibrary((HMODULE)ActiveRendererDLL);
			ActiveRenderer = nullptr;
			return;
		}

		void* destroyRendererFn = GetProcAddress((HMODULE)ActiveRendererDLL, "DestroyRenderer");
		if (!destroyRendererFn)
		{
			FreeLibrary((HMODULE)ActiveRendererDLL);
			ActiveRenderer = nullptr;
			return;
		}

		DestroyRenderer = reinterpret_cast<DestroyRendererFn>(destroyRendererFn);

		CreateRendererFn createRenderer = reinterpret_cast<CreateRendererFn>(createRendererFn);
		ActiveRenderer = createRenderer();
	}

	IRenderer& RendererManager::GetRenderer()
	{
		return *ActiveRenderer;
	}
}
