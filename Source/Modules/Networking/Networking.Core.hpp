#pragma once

#ifdef Networking_EXPORTS
#define NETWORKING_API __declspec(dllexport)
#elif Networking_IMPORTS
#define NETWORKING_API __declspec(dllimport)
#else
#define  NETWORKING_API
#endif