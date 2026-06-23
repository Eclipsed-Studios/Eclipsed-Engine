#pragma once

#include "ClassRegistry.h"

template<typename T>
struct TypeRegistrar
{
    TypeRegistrar(ClassRegistry& reg);
};

template<typename T>
inline TypeRegistrar<T>::TypeRegistrar(ClassRegistry& reg)
{
    static T info;
    reg.Register(T::Name, &info);
}