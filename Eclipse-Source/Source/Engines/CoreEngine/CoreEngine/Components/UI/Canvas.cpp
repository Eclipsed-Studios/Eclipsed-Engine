#include "Canvas.h"

#include "GraphicsEngine/OpenGL/DebugDrawers/DebugDrawer.h"

namespace Eclipse
{
    void Canvas::EarlyUpdate()
    {
        if (drawCanvasGizmos)
        {
            float size = ReferenceResolution->x / ReferenceResolution->y;

            Math::Vector2f sqrPosition = gameObject->transform->GetPosition() * 0.5f + Math::Vector2f(0.5f, 0.5f);
            float sqrRotation = gameObject->transform->GetRotation();
            Math::Vector2f sqrSize = Math::Vector2f(0.5f * size, 0.5f);

            DebugDrawer::DrawSquare(sqrPosition, sqrRotation, sqrSize, Math::Color(0.9f, 0.9f, 0.9f, 1.f));
        }
    }
}