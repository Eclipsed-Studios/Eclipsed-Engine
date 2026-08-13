#pragma once

#include <string>

#include "Networking.Core.hpp"

namespace Eclipse
{
    class NETWORKING_API General
    {
    public:
        static std::string GetPublicIPAdress();
    };
}