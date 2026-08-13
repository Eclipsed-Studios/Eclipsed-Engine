#pragma once

#ifdef Physics_EXPORTS
#define PHYSICS_API __declspec(dllexport)
#elif Physics_IMPORTS
#define PHYSICS_API __declspec(dllimport)
#else
#define  PHYSICS_API
#endif