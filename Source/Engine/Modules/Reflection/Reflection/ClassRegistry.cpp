#include "ClassRegistry.h"

void ClassRegistry::Register(const char* name, ClassInfoBase* info)
{
    GetMap()[name] = info;
}

ClassInfoBase* ClassRegistry::Get(const char* name)
{
    auto& map = GetMap();
    auto it = map.find(name);

    return it != map.end() ? it->second : nullptr;
}

std::map<std::string, ClassInfoBase*, std::less<>>& ClassRegistry::GetMap()
{
    return map;
}
