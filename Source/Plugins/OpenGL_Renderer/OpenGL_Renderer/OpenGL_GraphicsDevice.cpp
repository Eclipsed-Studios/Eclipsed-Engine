#include "OpenGL_GraphicsDevice.h"

#include "OpenGL/glad/glad.h"

namespace Eclipse::Graphics::OpenGL
{
	Sprite* OpenGL_GraphicsDevice::CreateSprite()
	{
        Sprite* sprite = new Sprite;

        glGenVertexArrays(1, &sprite->GetSpriteBufferID());
        glBindVertexArray(sprite->GetSpriteBufferID());

        glGenBuffers(1, &sprite->GetVertexBufferID());
        glGenBuffers(1, &sprite->GetIndexBufferID());

        glBindBuffer(GL_ARRAY_BUFFER, sprite->GetVertexBufferID());
        glBufferData(GL_ARRAY_BUFFER, sizeof(sprite->Verticies), sprite->Verticies, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite->GetIndexBufferID());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sprite->Indices), sprite->Indices, GL_STATIC_DRAW);

        {
            // glVertexAttribPointer(shader layout index, total number of floats/ints/bools etc, GL_[your type], GL_FALSE, vertex stride, offset from last layout position start)
            // Matrix4x4 would be index 0, 1, 2 and 3 set as in setting 4 float4's

            size_t offset = 0;
            // Position
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Sprite::Vertex), (void*)offset);
            offset += 2 * sizeof(float);

            // TexCoord
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Sprite::Vertex), (void*)offset);
            offset += 2 * sizeof(float);

            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(0);
        }

        glBindVertexArray(0);

		return nullptr;
	}

    TextSprite* OpenGL_GraphicsDevice::CreateTextSprite()
    {
        TextSprite* sprite = new TextSprite;
        glGenVertexArrays(1, &sprite->GetSpriteBufferID());
        glBindVertexArray(sprite->GetSpriteBufferID());

        glGenBuffers(1, &sprite->GetVertexBufferID());
        glGenBuffers(1, &sprite->GetIndexBufferID());

        glBindBuffer(GL_ARRAY_BUFFER, sprite->GetVertexBufferID());
        glBufferData(GL_ARRAY_BUFFER, sizeof(sprite->Vertices), sprite->Vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite->GetIndexBufferID());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sprite->Indices), sprite->Indices, GL_STATIC_DRAW);

        {
            // glVertexAttribPointer(shader layout index, total number of floats/ints/bools etc, GL_[your type], GL_FALSE, vertex stride, offset from last layout position start)
            // Matrix4x4 would be index 0, 1, 2 and 3 set as in setting 4 float4's

            size_t offset = 0;
            // Position
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(TextSprite::Vertex), (void*)offset);
            offset += 2 * sizeof(float);

            // TexCoord
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(TextSprite::Vertex), (void*)offset);
            offset += 2 * sizeof(float);

            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(0);
        }

        glBindVertexArray(0);
        return nullptr;
    }
}

