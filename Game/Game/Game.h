#pragma once

namespace Eclipse
{
    class Game
    {
    public:
        Game() = delete;
        ~Game() = delete;

        static void Init();
        
        #ifndef _GAME
            static inline bool IsPlaying = false;
            static inline bool IsPaused = false;
        #endif
    };
}