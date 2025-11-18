#pragma once

#include "EntityEngine/Components/Base/BaseComponent.h"

#include "AssetEngine/Assets/VertexShader.h"
#include "AssetEngine/Assets/PixelShader.h"

#include "AssetEngine/PathManager.h"


namespace Eclipse
{
    class TextMaterial
    {
    public:
        TextMaterial();
        void Use(unsigned textureID);

        VertexShader vertexShader;
        PixelShader pixelShader;

        unsigned programID = 0;

        Math::Color color;
    };

    class TextRenderer : public Component
    {
        COMPONENT_BASE_2(TextRenderer, 0)

    public:
        void EditorUpdate() override;

        void OnComponentAdded() override;
        void OnSceneLoaded() override;

        void Render() override;
        void Draw();

        void SetFont(const char* aFont);
        void SetFontSize(int aFontSize);

        void SetText(const char* aText);

        //void DrawInspector() override;

        //void DrawMultilineInspector();
        //void DrawAlignmentInspector(const ImColor& onColor, const ImColor& offColor);
        //void DrawCenteringInspector(const ImColor& onColor, const ImColor& offColor);

        void OnDrawGizmos() override;
        
        PRIVATE_SERIALIZED_FIELD_DEFAULT(std::string, myText, "E");
        PRIVATE_SERIALIZED_FIELD_DEFAULT(Math::Color, myTextColor, Math::Color(1, 1, 1, 1));

        SERIALIZED_FIELD_DEFAULT(std::string, myFontPath, (PathManager::GetEngineAssets() / "Fonts/Quicksand-VariableFont_wght.ttf").generic_string());
        SERIALIZED_FIELD_DEFAULT(int, myFontSize, 48);

        SERIALIZED_FIELD_DEFAULT(Math::Vector2f, myRect, Math::Vector2f(1.f, 1.f));
        SERIALIZED_FIELD_DEFAULT(float, myCharacterSpacing, 1.f);
        SERIALIZED_FIELD_DEFAULT(float, myEnterSpacing, 1.f);

        int myLastFontSize = 48;

        static inline bool drawRectGizmos = false;

    private:
        class Font* myFont;
        TextMaterial* myMaterial;

        bool myCreatedRenderer = false;

        PRIVATE_SERIALIZED_FIELD_DEFAULT(int, myTextAlignment, 0);
        PRIVATE_SERIALIZED_FIELD_DEFAULT(int, myTextCentering, 0);

        std::vector<float> lineOffsets;
    };
}