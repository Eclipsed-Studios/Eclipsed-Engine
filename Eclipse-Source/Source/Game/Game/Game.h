#pragma once

namespace Eclipse
{
    class Game
    {
    public:
        Game() = default;
        ~Game() = default;

        void Init();
        void Update();
        void Start();
        
        #ifndef _GAME
            bool myIsPlaying = false;
            bool myIsPaused = false;
        #endif
    };
}