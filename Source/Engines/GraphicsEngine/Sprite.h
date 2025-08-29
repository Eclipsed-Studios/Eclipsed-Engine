#pragma once

// TODO: Move this to a component once ECS is complete.

namespace ENGINE_NAMESPACE
{
    class Sprite
    {
    public:
        Sprite() = default;
        ~Sprite() = default;

        void Render();
        void Init();

    private:
        
        unsigned myVTXbuffer;
        unsigned myIDXbuffer;
        unsigned mySpriteBuffer;


    private:
        struct Vertex
        {
            float posX;
            float posY;

            float colR;
            float colG;
            float colB;
        };

#pragma region hard_coded_verts_indecies
        // 4 vertices
        static inline Vertex vertices[]{
            {0, 0, 1, 0, 0},
            {1, 0, 0, 1, 0},
            {0, 1, 0, 0, 1},
            {1, 1, 1, 1, 0}};

        // 6 indices
        static inline unsigned indices[]{
            0, 1, 2,
            2, 1, 3};

#pragma endregion
    };
}