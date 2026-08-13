#include "EclipsedEngine.h"

#include "EclipsedEngine/Graphics/RendererManager.h"
#include "EclipsedEngine/Graphics/IRenderer.h"

#include "ImGui/imgui.h"

#include "MainSingleton.h"

void Eclipse::Engine::Test()
{
	Eclipse::Graphics::RendererManager::LoadRenderer("C:/Users/zulto/Desktop/MyFiles/Projects/Eclipsed-Engine/Bin/Eclipsed.OpenGL_Renderer.dll");
	Graphics::IRenderer& r = Eclipse::Graphics::RendererManager::GetRenderer();
	
	r.Init();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiContext* ctx = ImGui::GetCurrentContext();

	r.ImplImGui(ctx);
}

bool Eclipse::Engine::ShouldClose()
{
	Graphics::IRenderer& r = Eclipse::Graphics::RendererManager::GetRenderer();
	return r.ShouldWindowClose();
}


void Eclipse::Engine::EndFrame()
{
	Graphics::IRenderer& r = Eclipse::Graphics::RendererManager::GetRenderer();
	r.EndFrame();
}

void Eclipse::Engine::BeginFrame()
{
	Graphics::IRenderer& r = Eclipse::Graphics::RendererManager::GetRenderer();
	r.BeginFrame();

	r.ImGui_NewFrame();

	ImGui::NewFrame();
}

void Eclipse::Engine::Render()
{
	ImGui::Begin("Simon");
	ImGui::End();

	ImGui::Render();

	Graphics::IRenderer& r = Eclipse::Graphics::RendererManager::GetRenderer();
	r.Render();
}