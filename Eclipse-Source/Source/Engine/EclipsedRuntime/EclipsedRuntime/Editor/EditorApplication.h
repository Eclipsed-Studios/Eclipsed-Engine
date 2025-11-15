#pragma once

#include "EclipsedRuntime/Runtime_Defines.h"

#include "EclipsedRuntime/Editor/EditorContext.h"

namespace Eclipse::Editor
{
    class ECL_RUNTIME_API EditorApplication
    {
    public:
        void Init();
        int Update();

        void Shutdown();

    private:
        EditorContexts myContext;
    };
}