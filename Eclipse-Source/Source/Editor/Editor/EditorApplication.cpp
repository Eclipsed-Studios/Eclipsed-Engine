#include "EditorApplication.h"

#ifdef ECLIPSED_EDITOR

#include "Utilities/ErrorCodes.h"
#include "GraphicsEngine/OpenGL/OpenGLGraphicsAPI.h"
#include "Editor/EditorProjectManager.h"


namespace Eclipse::Editor
{
    void EditorApplication::Init()
    {
        EditorProjectManager projectManager;
        std::string projectPath = projectManager.LoadOrSelectProject();

        myContext.Init(projectPath);
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