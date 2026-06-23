#pragma once

#include "EclipsedEngine/Components/Rendering/BaseRenderComponent.h"
#include "EclipsedEngine/Components/Component.h"

#include "AssetEngine/Assets/Shader/VertexShaderAsset.h"
#include "AssetEngine/Assets/Shader/PixelShaderAsset.h"
#include "AssetEngine/Assets/FontAsset.h"
#include "AssetEngine/Assets/MaterialAsset.h"

#include "CoreEngine/PathManager.h"
#include "CoreEngine/GraphicsBuffers/TextBuffer.h"
#include "CoreEngine/GraphicsBuffers/TextMaterialBuffer.h"
#include "CoreEngine/GraphicsBuffers/TransformBuffer.h"

#include "CoreEngine/Macros/defines.h"

ECLIPSED_CLASS;

namespace Eclipse
{
    class ECLIPSED_API TextRenderer : public BaseRenderComponent
    {
        COMPONENT_BASE_2(TextRenderer, 0)

    public:
#ifdef ECLIPSED_EDITOR
        void EditorUpdate() override;
#endif
        void OnComponentAdded() override;
        void TransformUpdate();

        void Render() override;
        void Draw();

        void SetFont(const char* aFont);
        void SetFontSize(float aFontSize);

        void SetText(const char* aText);

        //void DrawInspector() override;

        //void DrawMultilineInspector();
        //void DrawAlignmentInspector(const ImColor& onColor, const ImColor& offColor);
        //void DrawCenteringInspector(const ImColor& onColor, const ImColor& offColor);

#ifdef ECLIPSED_EDITOR
        void OnDrawGizmos() override;
#endif

        std::string myText = "TEXT";
        Math::Color myTextColor = Math::Color(1, 1, 1, 1);
        Assets::Font font;

        float myFontSize = 48.f;

        Math::Vector2f myRect = Math::Vector2f(1.f, 1.f);

        float myCharacterSpacing = 1.f;
        float myEnterSpacing = 1.f;
        float mySpaceSpacing = 1.f;

        int myLastFontSize = 48;

        static inline bool drawRectGizmos = false;

    private:
        Assets::Material material;

        int myTextAlignment = 1;
        int myTextCentering = 1;

        std::vector<float> lineOffsets;

        TextMaterialBuffer myTextMaterialBuffer;
        TransformBuffer myTransformBuffer;
        TextBuffer myTextBuffer;
    };
}
