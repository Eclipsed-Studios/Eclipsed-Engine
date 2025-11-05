#include "Canvas.h"

#include "GraphicsEngine/OpenGL/DebugDrawers/DebugDrawer.h"
#include "GraphicsEngine/OpenGL/UniformVariableManager.h"

namespace Eclipse
{
    COMPONENT_REGISTRATION(Canvas);


    void Canvas::SetCanvasTransformProperties()
    {
        int isScene;
        GraphicsEngine::GetGlobalUniform(UniformType::Int, "IsSceneWindow", &isScene);
        float aspectRatio;
        GraphicsEngine::GetGlobalUniform(UniformType::Float, "resolutionRatio", &aspectRatio);

        Math::Vector2f sceneScale;
        GraphicsEngine::GetGlobalUniform(UniformType::Vector2f, "cameraScale", &sceneScale);

        //canvasCameraTransform.Rotation = gameObject->transform->GetRotation();

        canvasCameraTransform.PositionOffset = { 0.f, 0.f };
        canvasCameraTransform.ScaleMultiplier = Math::Vector2f(sceneScale.x * aspectRatio * 2.f * 0.888f, sceneScale.y);
        canvasCameraTransform.ScaleMultiplier *= gameObject->transform->GetScale();

        if (!isScene)
            return;

        Math::Vector2f scenePosition;
        GraphicsEngine::GetGlobalUniform(UniformType::Vector2f, "cameraPosition", &scenePosition);

        canvasCameraTransform.PositionOffset = (scenePosition * -1.f) * ReferenceResolution;
        canvasCameraTransform.PositionOffset += gameObject->transform->GetPosition() * ReferenceResolution;
        canvasCameraTransform.PositionOffset *= Math::Vector2f(aspectRatio, 1.f) * sceneScale;

        float sceneRotation;
        GraphicsEngine::GetGlobalUniform(UniformType::Float, "cameraRotation", &sceneRotation);
        canvasCameraTransform.Rotation += sceneRotation;
    }

    void Canvas::EditorUpdate()
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