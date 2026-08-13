#pragma once
#ifdef ECL_EDITOR

#include "EclipsedEngine/Editor/EditorContext.h"
#include "EclipsedEngine.Core.hpp"

namespace Eclipse::Editor
{
    class ECL_API EditorApplication
    {
    public:
        void Init(const char* aPath);
        int Update();

        void Shutdown();

    private:
        EditorContexts myContext;
    };
}
#endif