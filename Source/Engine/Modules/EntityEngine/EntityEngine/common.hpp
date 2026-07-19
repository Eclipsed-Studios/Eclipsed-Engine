#pragma once

#ifdef EntityEngine_EXPORTS
#define ECS_API __declspec(dllexport)
#elif EntityEngine_IMPORTS
#define ECS_API __declspec(dllimport)
#else 
#define ECS_API 
#endif