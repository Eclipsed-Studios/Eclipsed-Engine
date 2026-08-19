#pragma once

#include <string>
#include <fstream>

#include "EclipsedEngine/Assets/Core/GUID.h"
#include "EclipsedEngine.Core.hpp"

namespace Eclipse::Assets
{
    class ECL_API BinaryReader
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

        void SetRead(size_t idx);

    private:
        std::ifstream file;
    };
}