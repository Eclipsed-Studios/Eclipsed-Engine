#pragma once

#include <string>
#include <fstream>

#include "AssetEngine/Core/GUID.h"

namespace Eclipse::Assets
{
    class BinaryReader
    {
    public:
        BinaryReader() = default;
        BinaryReader(const std::string& path);
        BinaryReader(const GUID& guid);

    public:
        bool Open(const std::string& path);
        void Read(void* data, size_t size);
        void Close();

        bool IsOpen() const;

    private:
        std::ifstream file;
    };
}