#include "TextManager.h"

#include "FreeType/ft2build.h"
#include "OpenGL/GLFW/glfw3.h"
#include "CoreEngine/Debug/DebugLogger.h"

#include FT_FREETYPE_H  

namespace Eclipse
{
    bool TextManager::Init()
    {
        if (FT_Init_FreeType(&freeType))
        {
            LOG_ERROR("FreeType/TextRenderer has FAILED to initilize");
            return false;
        }

        return true;
    }

    bool TextManager::CreateFont(const char* aFontPath, unsigned fontSize)
    {
        FT_Face face;
        if (FT_New_Face(freeType, aFontPath, 0, &face))
        {
            LOG_ERROR((("Font with path: ") + std::string(aFontPath) + " Failed to load correctly").c_str());
            return false;
        }
        FT_Set_Pixel_Sizes(face, 0, fontSize);

        Font font;
        for (int i = 0; i < 128; i++)
        {
            char characterChar = (char)i;
            if (FT_Load_Char(face, characterChar, FT_LOAD_RENDER))
            {
                LOG_ERROR((("Failed to load character: ") + std::string(&characterChar)).c_str());
                return false;
            }

            if (face->glyph->bitmap.buffer == 0)
                continue;

            unsigned texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            Character character = {
                texture,
                Math::Vector2i(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                Math::Vector2i(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
            };

            font.myCharTexture.emplace(characterChar, character);
        }

        font.maxCharHeight = (float)(face->max_advance_height >> 6) * 0.01f;

        std::stringstream fontKeyStream;
        fontKeyStream << aFontPath;
        fontKeyStream << fontSize;

        myFontMap.emplace(fontKeyStream.str(), font);

        FT_Done_Face(face);

        return true;
    }
}