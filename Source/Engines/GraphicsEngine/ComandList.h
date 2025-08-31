#pragma once

#include "RenderCommand.h"

#include <vector>

class ComandList
{
public:
    ComandList() = default;
    ~ComandList() = default;

private:
    std::vector<RenderCommandBase> myRenderCommands;
};