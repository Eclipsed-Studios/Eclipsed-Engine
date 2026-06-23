#pragma once

#include <string>
#include <map>

#include "ReflectionType.h"

class ClassRegistry
{
public:
    void Register(const char* name, ClassInfoBase* info);

    ClassInfoBase* Get(const char* name);

    std::map<std::string, ClassInfoBase*, std::less<>>& GetMap();

    std::map<std::string, ClassInfoBase*, std::less<>> map;
};