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
    };
}