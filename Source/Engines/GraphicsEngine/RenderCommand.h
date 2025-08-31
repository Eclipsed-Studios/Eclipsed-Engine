#pragma once

class RenderCommandBase
{
public:
    RenderCommand() = default;
    ~RenderCommand() = default;
    
    void Execute();
};