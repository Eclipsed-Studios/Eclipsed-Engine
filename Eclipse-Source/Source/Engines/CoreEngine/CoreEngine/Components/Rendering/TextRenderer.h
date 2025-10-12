#pragma once

#include "Components/Base/BaseComponent.h"


namespace Eclipse
{
    class TextMaterial
    {
    public:
        TextMaterial();
        void Use(unsigned textureID);

        class Shader* myShader;

        Math::Color color;
    };

    class TextRenderer : public Component
    {
        BASE_SELECTION(TextRenderer, 0)

    public:
        void EditorUpdate() override;

        void OnComponentAdded() override;
        void OnSceneLoaded() override;

        void Render() override;
        void Draw();

        void SetFont(const char* aFont);
        void SetFontSize(int aFontSize);

        void SetText(const char* aText);

        SERIALIZED_FIELD_DEFAULT(std::string, myFontPath, "../Assets/Quicksand-VariableFont_wght.ttf");
        SERIALIZED_FIELD_DEFAULT(int, myFontSize, 48);
        int myLastFontSize = 48;

        SERIALIZED_FIELD_DEFAULT(std::string, myText, "E");


    private:
        class Font* myFont;

        TextMaterial* myMaterial;

        bool myCreatedRenderer = false;
    };
}