#pragma once

#ifdef ECS_EXPORTS
#define ECS_API __declspec(dllexport)
#elif ECS_IMPORTS
#define ECS_API __declspec(dllimport)
#else
#define  ECS_API
#endif