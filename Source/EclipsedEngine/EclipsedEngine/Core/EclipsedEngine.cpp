#include "EclipsedEngine.h"

#include "EclipsedEngine/Graphics/RendererManager.h"
#include "EclipsedEngine/Graphics/IRenderer.h"

#include "MainSingleton.h"
#include "ImGui/imgui.h"

void Eclipse::Engine::Init()
{
	Eclipse::Graphics::RendererManager::LoadRenderer("C:/Users/zulto/Desktop/MyFiles/Projects/Eclipsed-Engine/Bin/Eclipsed.OpenGL_Renderer.dll");
	Graphics::IRenderer& r = Eclipse::Graphics::RendererManager::GetRenderer();

	r.Init();

	input = r.CreateInput();
	input->Init();

	ImGui_Init();
}



bool Eclipse::Engine::ShouldClose()
{
	Graphics::IRenderer& r = Eclipse::Graphics::RendererManager::GetRenderer();
	return r.ShouldWindowClose();
}

void* Eclipse::Engine::GetImGuiContext()
{
	return ImGui::GetCurrentContext();
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
	input->Update();

	ImGui_NewFrame();
}

void Eclipse::Engine::Render()
{
	Graphics::IRenderer& r = Eclipse::Graphics::RendererManager::GetRenderer();
	r.Render();

	ImGui_Render();
}



void Eclipse::Engine::ImGui_Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	Graphics::IRenderer& r = Eclipse::Graphics::RendererManager::GetRenderer();
	r.ImGui_Init(ImGui::GetCurrentContext());
}

void Eclipse::Engine::ImGui_NewFrame()
{
	Graphics::IRenderer& r = Eclipse::Graphics::RendererManager::GetRenderer();
	r.ImGui_NewFrame();
	ImGui::NewFrame();
}

void Eclipse::Engine::ImGui_Render()
{
	Graphics::IRenderer& r = Eclipse::Graphics::RendererManager::GetRenderer();
	ImGui::Render();
	r.ImGui_Render();
}