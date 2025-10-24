#pragma once

#ifdef ECLIPSED_EDITOR

#include "Editor/EditorContext.h"

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
#endif