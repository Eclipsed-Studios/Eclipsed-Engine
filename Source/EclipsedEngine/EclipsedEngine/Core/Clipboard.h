#pragma once

#include "EclipsedEngine.Core.hpp"

namespace Eclipse
{
    class ECL_API ClipBoard
    {
    public:
        static void CopyToClipboard(const void* aData, size_t aDataSize);
        static void* GetClipboardData();
    };
}