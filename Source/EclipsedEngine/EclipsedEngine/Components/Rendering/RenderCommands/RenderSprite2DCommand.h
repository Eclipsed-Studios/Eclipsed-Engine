#pragma once

#include "EclipsedEngine/Graphics/RenderCommands/RenderCommand.h"



namespace Eclipse
{
    class SpriteRenderer2D;
}

namespace Eclipse::Graphics
{
    class RenderSprite2DCommand : public RenderCommandBase
    {
    public:
        RenderSprite2DCommand(SpriteRenderer2D* aSpriterenderer) : mySpriteRenderer(aSpriterenderer)
        {}

        ~RenderSprite2DCommand() = default;

        void Execute() override;

    private:
        SpriteRenderer2D* mySpriteRenderer;
    };
}