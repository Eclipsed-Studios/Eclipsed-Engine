#pragma once

#include "EclipsedEngine/Editor/EditorContext.h"

namespace Eclipse::Editor
{
    class EditorApplication
    {
    public:
        void Init();
        int Update();

        void Shutdown();

    private:
        EditorContexts myContext;
    };
}