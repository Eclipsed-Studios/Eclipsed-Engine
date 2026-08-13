#include "EditorApplication.h"

#ifdef ECL_EDITOR

#include "EclipsedEngine/Editor/EditorProjectManager.h"
#include "Core/PathManager.h"

namespace Eclipse::Editor
{
	void EditorApplication::Init(const char* aPath)
	{
		if (strlen(aPath) <= 0)
		{
			std::string projectPath = EditorProjectManager::LoadOrSelectProject();
			myContext.Init(projectPath);
		}
		else
		{
			myContext.Init(aPath);
		}
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