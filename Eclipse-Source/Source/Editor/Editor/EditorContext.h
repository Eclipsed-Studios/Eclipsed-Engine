#pragma once

#ifdef ECLIPSED_EDITOR

#include "Editor/EditorRuntime.h"
#include "Editor/EditorUIManager.h"

namespace Eclipse::Editor
{
    class EditorContexts
    {
    public:
        void Init(const std::string& projectPath);

        bool BeginFrame();
        void Update();
        void Render();
        void EndFrame();

        void Shutdown();

    private:
        EditorRuntime myRuntime;
        EditorUIManager myUIManager;
    };
}
#endif