#pragma once

#ifdef ECLIPSED_EDITOR

#include "EclipsedRuntime/Editor/EditorRuntime.h"
#include "EclipsedRuntime/Editor/EditorUIManager.h"

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

        void Shutdown()
        {
            myRuntime.ShutDown();
        }

    private:
        EditorRuntime myRuntime;
        EditorUIManager myUIManager;
    };
}
#endif