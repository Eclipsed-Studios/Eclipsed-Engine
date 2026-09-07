#pragma once
#include <functional>
#include <cstddef>
#include <string>

#include "EclipsedEngine.Core.hpp"

namespace Eclipse::Assets
{
    /// <summary>
    /// ID class for the asset engine.
    /// </summary>
    struct ECL_API GUID
    {
        unsigned long long high = 0;
        unsigned long long low = 0;

        bool operator==(const GUID& other) const;
        bool operator!=(const GUID& other) const;

        static GUID GenerateGUID();
        void Generate();

        void FromString(const std::string& hashStr);
        std::string ToString() const;

        bool IsEmpty() const;
    };

    struct ECL_API GUIDHash
    {
        std::size_t operator()(const GUID& guid) const
        {
            return std::hash<unsigned long long>()(guid.high) ^
                (std::hash<unsigned long long>()(guid.low) << 1);
        }
    };
}