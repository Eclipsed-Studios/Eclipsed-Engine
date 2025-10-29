#include "UIImage.h"

#include "GraphicsEngine/Sprite.h"

#include "Components/UI/RectTransform.h"
#include "Components/UI/Canvas.h"

#include "GraphicsEngine/RenderCommands/CommandList.h"

namespace Eclipse
{
    COMPONENT_REGISTRATION(UIImage);

    void UIImage::OnComponentAdded()
    {
        myMaterial = new Material((PathManager::GetEngineAssets() / "Default/Shaders/ScreenSpaceSpritePixelShader.glsl").generic_string().c_str(), (PathManager::GetEngineAssets() / "Default/Shaders/ScreenSpaceSpriteVertexShader.glsl").generic_string().c_str());
    }

    void UIImage::Render()
    {
        CommandListManager::GetUICommandList().Enqueue([&]() {
            Draw();
            });
    }

    void UIImage::Draw()
    {
        if (!myMaterial)
            return;
        if (!Canvas::main)
            return;
        

        auto tranForm = gameObject->GetComponent<RectTransform>();

        Math::Vector2f position = tranForm->Position;
        position *= Canvas::canvasCameraTransform.ScaleMultiplier;
        position += Canvas::canvasCameraTransform.PositionOffset;

        Math::Vector2f scale = tranForm->WidthHeightPX * 2.f;
        scale *= Canvas::canvasCameraTransform.ScaleMultiplier;

        float rotation = 0.f;
        rotation += Canvas::canvasCameraTransform.Rotation;

        unsigned shaderID = myMaterial->myShader->GetProgramID();

        myMaterial->myShader->Use(shaderID);
        myMaterial->Use();

        GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "transform.position", &position);
        GraphicsEngine::SetUniform(UniformType::Float, shaderID, "transform.rotation", &rotation);
        GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "transform.size", &scale);

        //auto tempSettings = TemporarySettingsSingleton::Get();

        Math::Vector2f resolution = Canvas::main->ReferenceResolution;

        resolution.x = 1.f / resolution.x;
        resolution.y = 1.f / resolution.y;

        Math::Vector2f canvasScaleRelationOneDiv = { resolution.x, resolution.y };
        GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "canvasScaleRelationOneDiv", &canvasScaleRelationOneDiv);

        // Math::Vector4f pixelPickColor = gameObject->GetPixelPickingIDColor();
        // GraphicsEngine::SetUniform(UniformType::Vector4f, shaderID, "pixelPickColor", &pixelPickColor);

        GraphicsEngine::SetGlobalUniforms(shaderID);

        Sprite::Get().Render();
    }
}