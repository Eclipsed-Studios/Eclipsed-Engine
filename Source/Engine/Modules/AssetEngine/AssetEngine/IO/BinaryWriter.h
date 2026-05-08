#pragma once

#include <fstream>
#include <string>

#include "AssetEngine/Core/GUID.h"

#define WRITE(data) &data, sizeof(data)

namespace Eclipse::Assets
{
    class BinaryWriter
    {
    public:
        BinaryWriter() = default;
        BinaryWriter(const std::string& path);
        BinaryWriter(const GUID& guid);

    public:
        bool Open(const std::string& path);
        void Write(const void* data, size_t size);
        void Close();

        bool IsOpen() const;

    private:
        void CreateFile(const std::string& path);

    private:
        std::ofstream file;
    };
}