#pragma once

#define STRINGIFY(type) #type

#ifdef _NO_EXPORT
#define ECLIPSED_API
#else
#ifdef ECLIPSED_RUNTIME
#define ECLIPSED_RUNTIME_API __declspec(dllexport)
#else
#define ECLIPSED_RUNTIME_API __declspec(dllimport)
#endif
#endif