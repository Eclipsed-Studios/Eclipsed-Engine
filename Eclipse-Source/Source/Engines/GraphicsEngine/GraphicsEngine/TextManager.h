#pragma once

#include <unordered_map>
#include "Utilities/Math/Vector/Vector2.h"

#undef CreateFont

// This is typedefed as "FT_Library" in freetype
class FT_LibraryRec_;

namespace Eclipse
{
    struct Character
    {
        unsigned textureID;
        Math::Vector2i size;
        Math::Vector2i bearing;
        int advance;
    };
    struct Font
    {
        std::unordered_map<char, Character> myCharTexture;
        float maxCharHeight;
        unsigned size;
    };

    class TextManager
    {
        friend class GraphicsEngine;
    public:
        TextManager() = default;
        ~TextManager() = default;

        bool Init();
        bool CreateFont(const char* aFontPath, unsigned fontSize);

        Font& GetFont(const char* aFontPath, unsigned fontSize)
        {
            std::stringstream fontKeyStream;
            fontKeyStream << aFontPath;
            fontKeyStream << fontSize;

            std::string fontKey = fontKeyStream.str();

            if (myFontMap.find(fontKey) == myFontMap.end())
            {
                CreateFont(aFontPath, fontSize);
                return myFontMap.at(fontKey);
            }
            else
                return myFontMap.at(fontKey);

        }

        static TextManager& Get()
        {
            static TextManager instance;
            return instance;
        }

    private:

        std::unordered_map<std::string, Font> myFontMap;

        FT_LibraryRec_* freeType;
    };
}