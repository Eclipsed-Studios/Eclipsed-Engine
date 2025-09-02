#pragma once

namespace ENGINE_NAMESPACE
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