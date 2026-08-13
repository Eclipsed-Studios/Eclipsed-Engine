#pragma once

#ifdef Audio_EXPORTS
#define AUDIO_API __declspec(dllexport)
#elif Audio_IMPORTS
#define AUDIO_API __declspec(dllimport)
#else
#define  AUDIO_API
#endif