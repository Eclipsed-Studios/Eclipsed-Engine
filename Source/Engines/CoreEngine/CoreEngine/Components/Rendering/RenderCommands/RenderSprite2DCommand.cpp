#include "RenderSprite2DCommand.h"

#include "../SpriteRenderer2D.h"

namespace Eclipse
{
    void RenderSprite2DCommand::Execute()
    {
        mySpriteRenderer->Draw();
    }
}