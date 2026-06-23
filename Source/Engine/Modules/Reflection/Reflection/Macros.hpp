#pragma once

#include "ReflectionType.h"

#define BASE(cls) template<typename T> struct TypeInfo; 
#define TYPE_INFO_STRUCT(cls) template<> struct TypeInfo<cls> : ClassInfoBase

#define PROPERTY_LIST(...) static constexpr const Property* Properties[] = { __VA_ARGS__ };

#define TYPE(type) using TYPE = type;

#define EXPAND(x) x

#define PROPERTY(type, member) \
inline static const TypedProperty<TYPE, type> member \
{ \
#member, \
sizeof(type), \
&TYPE::member \
};

#define NAME(name) static constexpr const char* Name = #name;
#define GETTER_METHODS \
	inline const char* GetName() const override { return Name; }                \
inline const Property* const* GetProperties() const override { return Properties; }    \
inline size_t GetPropertyCount() const override { return PropertyCount; }


#define PROPERTY_COUNT(count) static constexpr const unsigned long long PropertyCount = count;

#define CONCAT_INNER(a, b) a##b
#define CONCAT(a, b) CONCAT_INNER(a, b)
#define REGISTRATOR(cls) static TypeRegistrar<TypeInfo<cls>> cls##_registrar_(Eclipse::EclipsedRuntime::Get().GetClassReg());