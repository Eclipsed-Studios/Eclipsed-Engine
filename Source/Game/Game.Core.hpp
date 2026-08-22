#pragma once

#ifdef Game_EXPORTS
#define GAME_API __declspec(dllexport)
#elif Game_IMPORTS
#define GAME_API __declspec(dllimport)
#else
#define  GAME_API
#endif