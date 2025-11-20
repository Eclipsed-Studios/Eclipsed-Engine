#pragma once

#include "ReplicatedVariable.h"
#include <vector>

namespace Eclipse
{
    class Replication
    {
    public:
        Replication() = default;
        ~Replication() = default;

        static inline std::vector<ReplicatedVariable> ReplicatedVariableList;
    };
}