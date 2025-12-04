#include "Engine.h"

#include "PhysicsEngine/PhysicsEngine.h"
#include "GraphicsEngine/OpenGL/OpenGLGraphicsAPI.h"



#include "InputEngine/Input.h"
#include "InputEngine/InputMapper.h"

#include "EntityEngine/ComponentManager.h"
#include "Utilities/PlatformIntegration/IntegrationManager.h"

#include <iostream>
#include "Utilities/Reflection/Reflection.h"
#include "Scenes/SceneLoader.h"
#include "Scenes/SceneManager.h"

#include "EntityEngine/Components/AudioSource.h"

#include "EngineSettings.h"

#include "AssetEngine/Resources.h"
#include "AssetEngine/Assets/Texture.h"

#include "GraphicsEngine/RenderCommands/CommandList.h"

namespace Eclipse
{
	void Engine::Init()
	{

		ComponentManager::Init();

		SceneManager::LoadSceneData();
		Time::Init();
		Input::Init();
	}


	void Engine::BeginFrame()
	{
		Assets::Resources::Update();
	}

	void Engine::Update()
	{
		CommandListManager::GetHappenAtBeginCommandList().Execute();
		CommandListManager::GetHappenAtBeginCommandList().Reset();

		DebugInformationCollector::ResetRenderCalls();

		PlatformIntegration::IntegrationManager::Update();

		Time::Update();
		Input::Update();
	}

	void Engine::Render()
	{

	}

	void Engine::EndFrame()
	{
	}
}