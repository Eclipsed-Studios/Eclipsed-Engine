#pragma once

#define STRINGIFY(type) #type


#ifdef _ECLIPSED_EXPORT_DLL
#define ECLIPSED_API __declspec(dllexport)
#else
#define ECLIPSED_API __declspec(dllimport)
#endif