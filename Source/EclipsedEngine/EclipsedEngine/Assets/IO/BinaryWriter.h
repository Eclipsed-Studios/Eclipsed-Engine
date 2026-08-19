#pragma once

#include <fstream>
#include <string>
#include <filesystem>

#include "EclipsedEngine/Assets/Core/GUID.h"
#include "EclipsedEngine.Core.hpp"

#define DATA_SIZE_PAIR(data) &data, sizeof(data)

namespace Eclipse::Assets
{
    class ECL_API BinaryWriter
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

        std::filesystem::path GetPath() const;

    private:
        void CreateFile(const std::string& path);

    private:
        std::filesystem::path path;
        std::ofstream file;
    };
}