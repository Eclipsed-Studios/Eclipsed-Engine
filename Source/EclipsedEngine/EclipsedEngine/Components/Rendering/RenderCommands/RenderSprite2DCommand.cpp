#include "RenderSprite2DCommand.h"

#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"

namespace Eclipse::Graphics
{
    void RenderSprite2DCommand::Execute()
    {
        mySpriteRenderer->Draw();
    }
}