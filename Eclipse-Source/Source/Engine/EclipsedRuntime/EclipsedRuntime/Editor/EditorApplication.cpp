#include "EditorApplication.h"

#ifdef ECLIPSED_EDITOR

#include "Utilities/ErrorCodes.h"
#include "GraphicsEngine/OpenGL/OpenGLGraphicsAPI.h"
#include "EclipsedRuntime/Editor/EditorProjectManager.h"
#include <NetworkEngine\Client\Client.h>


namespace Eclipse::Editor
{
	void EditorApplication::Init()
	{
		EditorProjectManager projectManager;
		std::string projectPath = projectManager.LoadOrSelectProject();

		myContext.Init(projectPath);

		//PlatformIntegration::Discord::SetupWithID(1425504148681658383);
		//PlatformIntegration::Discord::SetLargeImage("eclipsemoonnobg");
	}

	int EditorApplication::Update()
	{
		int shouldClose = myContext.BeginFrame();
		myContext.Update();
		myContext.Render();
		myContext.EndFrame();

		return shouldClose;
	}

	void EditorApplication::Shutdown()
	{
		myContext.Shutdown();
	}
}
#endif