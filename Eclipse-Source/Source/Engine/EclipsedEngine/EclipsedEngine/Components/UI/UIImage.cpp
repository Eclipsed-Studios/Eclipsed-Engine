#include "UIImage.h"

#include "GraphicsEngine/Sprite.h"

#include "AssetEngine/Resources.h"

#include "EclipsedEngine/Components/UI/RectTransform.h"
#include "EclipsedEngine/Components/UI/Canvas.h"

#include "GraphicsEngine/RenderCommands/CommandList.h"

namespace Eclipse
{
    //void UIImage::OnComponentAdded()
    //{
    //    myMaterial = Resourcess::Get<Materials>();
    //    myMaterial = new Material((PathManager::GetEngineAssetsPath() / "Default/Shaders/ScreenSpaceSpritePixelShader.glsl").generic_string().c_str(), (PathManager::GetEngineAssetsPath() / "Default/Shaders/ScreenSpaceSpriteVertexShader.glsl").generic_string().c_str());
    //}

    //void UIImage::Render()
    //{
    //    CommandListManager::GetUICommandList().Enqueue([&]() {
    //        Draw();
    //        });
    //}

    //void UIImage::Draw()
    //{
    //    if (!myMaterial)
    //        return;

    //    auto tranform = gameObject->GetComponent<RectTransform>();

    //    if (!tranform)
    //        return;
    //    if (!tranform->myCanvas)
    //        return;
    //        
    //    tranform->myCanvas->SetCanvasTransformProperties();

    //    Canvas::EditorCanvasCameraTransform& canvasCameraTransform = tranform->myCanvas->canvasCameraTransform;

    //    Math::Vector2f position = tranform->Position;
    //    position *= canvasCameraTransform.ScaleMultiplier;
    //    position += canvasCameraTransform.PositionOffset;

    //    Math::Vector2f scale = tranform->WidthHeightPX * 2.f;
    //    scale *= canvasCameraTransform.ScaleMultiplier;

    //    float rotation = 0.f;
    //    rotation += canvasCameraTransform.Rotation;

    //    unsigned shaderID = myMaterial->myShader->GetProgramID();

    //    myMaterial->myShader->Use(shaderID);
    //    myMaterial->Use();

    //    GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "transform.position", &position);
    //    GraphicsEngine::SetUniform(UniformType::Float, shaderID, "transform.rotation", &rotation);
    //    GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "transform.size", &scale);

    //    //auto tempSettings = TemporarySettingsSingleton::Get();

    //    Math::Vector2f resolution = tranform->myCanvas->ReferenceResolution;

    //    resolution.x = 1.f / resolution.x;
    //    resolution.y = 1.f / resolution.y;

    //    Math::Vector2f canvasScaleRelationOneDiv = { resolution.x, resolution.y };
    //    GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "canvasScaleRelationOneDiv", &canvasScaleRelationOneDiv);

    //    // Math::Vector4f pixelPickColor = gameObject->GetPixelPickingIDColor();
    //    // GraphicsEngine::SetUniform(UniformType::Vector4f, shaderID, "pixelPickColor", &pixelPickColor);

    //    GraphicsEngine::SetGlobalUniforms(shaderID);

    //    Sprite::Get().Render();
    //}
}