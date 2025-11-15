#ifndef _ECL_RUNTIME_DEFINES
#define _ECL_RUNTIME_DEFINES

#ifdef ECLIPSED_EXPORT_RUNTIME
#define ECL_RUNTIME_API __declspec(dllexport)
#else
#define ECL_RUNTIME_API __declspec(dllimport)
#endif

#endif