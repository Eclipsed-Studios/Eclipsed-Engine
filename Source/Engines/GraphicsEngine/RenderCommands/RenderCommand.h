#pragma once    

class RenderCommandBase
{
public:
    RenderCommandBase() = default;
    ~RenderCommandBase() = default;

    virtual void Execute() = 0;

    RenderCommandBase* next = nullptr;
};