#pragma once

#ifdef Assets_EXPORTS
#define ASSET_API __declspec(dllexport)
#elif Assets_IMPORTS
#define ASSET_API __declspec(dllimport)
#else
#define  ASSET_API
#endif