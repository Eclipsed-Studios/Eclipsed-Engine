#pragma once

// This is typedefed as "FT_Library" in freetype
class FT_LibraryRec_;

namespace Eclipse
{
    class TextManager
    {
        friend class Renderer;
    public:
        TextManager();
        ~TextManager();

        FT_LibraryRec_* freeType;
    };
}