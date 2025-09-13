#pragma once

#include "RenderCommands/RenderCommand.h"

namespace Eclipse
{
    class RenderSprite2DCommand : public RenderCommandBase
    {
    public:
        RenderSprite2DCommand(SpriteRenderer2D* aSpriteRend) : mySpriteRenderer(aSpriteRend)
        {}
        ~RenderSprite2DCommand() = default;

        void Execute() override;

    private:
        class SpriteRenderer2D* mySpriteRenderer;
    };
}