#pragma once

namespace Eclipse
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

            float texCoordX;
            float texCoordY;
        };

#pragma region hard_coded_verts_indecies
        // 4 vertices
        static inline Vertex vertices[]{
            {-1.f, -1.f, 0, 0},
            {1.f, -1.f, 1, 0},
            {-1.f, 1.f, 0, 1},
            {1.f, 1.f, 1, 1}};

        // 6 indices
        static inline unsigned indices[]{
            0, 1, 2,
            2, 1, 3};

#pragma endregion
    };
}