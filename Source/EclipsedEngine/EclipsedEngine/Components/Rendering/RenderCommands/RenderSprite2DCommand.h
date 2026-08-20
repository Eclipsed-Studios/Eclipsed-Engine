#pragma once

#include "EclipsedEngine/Graphics/RenderCommands/RenderCommand.h"



namespace Eclipse::Graphics
{
    class SpriteRenderer2D;
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