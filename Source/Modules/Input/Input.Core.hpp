#pragma once

#ifdef Input_EXPORTS
#define INPUT_API __declspec(dllexport)
#elif Input_IMPORTS
#define INPUT_API __declspec(dllimport)
#else
#define  INPUT_API
#endif