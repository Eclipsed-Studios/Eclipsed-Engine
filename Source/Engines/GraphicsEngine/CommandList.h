#pragma once

//#include "RenderCommand.h"

#include <vector>
#include <functional>

namespace Eclipse
{
    class CommandList
    {
    public:
        static void Emplace(const std::function<void()>& aCommand);

        static void Execute();
        static void Clear();

    private:
        static inline std::vector<std::function<void()>> myCommandList;
    };
}