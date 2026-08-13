#pragma once

#ifdef EclipsedEngine_EXPORTS
#define ECL_API __declspec(dllexport)
#elif EclipsedEngine_IMPORTS
#define ECL_API __declspec(dllimport)
#else
#define  ECL_API
#endif