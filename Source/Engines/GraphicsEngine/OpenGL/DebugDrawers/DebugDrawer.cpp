#include "DebugDrawer.h"

#include "Math/Vector/Vector2.h"
#include "glad/glad.h"

#include "TemporarySettingsSingleton.h"

static const char* vtxShaderSource =
"#version 460 core\n"
"layout(location = 0)in vec2 VertexPosition;\n"
"layout(location = 1)in vec2 trash;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(VertexPosition * 2 - 1, 0, 1);\n"
"}\n";

static const char* pixelShaderSource =
"#version 460 core\n"
"out vec4 frag_colour;\n"
"uniform vec4 color;\n"
"void main()\n"
"{\n"
"frag_colour = color;\n"
"}\n";

namespace ENGINE_NAMESPACE
{
    void DebugDrawer::Init()
    {
        glGenVertexArrays(1, &myLineBuffer);
        glBindVertexArray(myLineBuffer);

        glGenBuffers(1, &myVTXbuffer);
        glGenBuffers(1, &myIDXbuffer);

        glBindBuffer(GL_ARRAY_BUFFER, myVTXbuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myIDXbuffer);

        {
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Math::Vector2f), (void*)0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Math::Vector2f), (void*)0);

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
        }

        vtxShaderID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vtxShaderID, 1, &vtxShaderSource, NULL);
        glCompileShader(vtxShaderID);

        pixelShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(pixelShaderID, 1, &pixelShaderSource, NULL);
        glCompileShader(pixelShaderID);

        programID = glCreateProgram();
        glAttachShader(programID, vtxShaderID);
        glAttachShader(programID, pixelShaderID);
        glLinkProgram(programID);
    }

    void DebugDrawer::Render()
    {
        glUseProgram(programID);

        for (auto& line : myLineCollection)
        {
            for (int i = 0; i < line.linePoints.size(); i++)
            {
                auto& temporarySingleton = TemporarySettingsSingleton::Get();

                float oneDivResX = temporarySingleton.GetOneDivResolutionX();
                float oneDivResY = temporarySingleton.GetOneDivResolutionY();

                LineVTX vert;
                vert.posX = line.linePoints[i].x;// * oneDivResX;
                vert.posY = line.linePoints[i].y;// * oneDivResY;

                vertices.emplace_back(vert);
                indices.emplace_back(i);
            }

            glBindBuffer(GL_ARRAY_BUFFER, myVTXbuffer);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(LineVTX), vertices.data(), GL_DYNAMIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myIDXbuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_DYNAMIC_DRAW);

            glBindVertexArray(myLineBuffer);

            unsigned location = glGetUniformLocation(programID, "color");
            glUniform4f(location, line.color.r, line.color.g, line.color.b, line.color.a);

            glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);

            indices.clear();
            vertices.clear();
        }

        myLineCollection.clear();
    }

    void DebugDrawer::DrawLine(Math::Vector2f aStart, Math::Vector2f aEnd, const Math::Color& aColor)
    {
        auto& line = DebugDrawer::Get().myLineCollection.emplace_back();
        line.color = aColor;

        line.linePoints.emplace_back(aStart);
        line.linePoints.emplace_back(aEnd);

    }
    void DebugDrawer::DrawRay(Math::Vector2f aStartPos, Math::Vector2f aDirection, const Math::Color& aColor)
    {
        auto& line = DebugDrawer::Get().myLineCollection.emplace_back();
        line.color = aColor;

        line.linePoints.emplace_back(aStartPos);
        line.linePoints.emplace_back(aStartPos + aDirection);
    }
    void DebugDrawer::DrawArrow(Math::Vector2f aStartPos, Math::Vector2f aDirection, const Math::Color& aColor)
    {
        auto& line = DebugDrawer::Get().myLineCollection.emplace_back();
        line.color = aColor;

        Math::Vector2f endPosition = aStartPos + aDirection;

        line.linePoints.emplace_back(aStartPos);
        line.linePoints.emplace_back(endPosition);

        Math::Vector2f directionNormalized = aDirection.Normalized();
        Math::Vector2f arrowCornersStart = endPosition - directionNormalized * 30.f;

        Math::Vector2f rightVector = Math::Vector2f(directionNormalized.y, -directionNormalized.x);

        Math::Vector2f rightArrowCorner = arrowCornersStart + rightVector * 30.f;
        Math::Vector2f leftArrowCorner = arrowCornersStart - rightVector * 30.f;

        line.linePoints.emplace_back(endPosition);
        line.linePoints.emplace_back(leftArrowCorner);

        line.linePoints.emplace_back(endPosition);
        line.linePoints.emplace_back(rightArrowCorner);
    }

    void DebugDrawer::DrawSquare(Math::Vector2f aPosition, Math::Vector2f aHalfExtents, const Math::Color& aColor)
    {
        auto& line = DebugDrawer::Get().myLineCollection.emplace_back();
        line.color = aColor;

        line.linePoints.emplace_back(aPosition - aHalfExtents);
        line.linePoints.emplace_back(aPosition + Math::Vector2f{ -aHalfExtents.x, aHalfExtents.y });

        line.linePoints.emplace_back(aPosition + Math::Vector2f{ -aHalfExtents.x, aHalfExtents.y });
        line.linePoints.emplace_back(aPosition + aHalfExtents);

        line.linePoints.emplace_back(aPosition + aHalfExtents);
        line.linePoints.emplace_back(aPosition + Math::Vector2f{ aHalfExtents.x, -aHalfExtents.y });

        line.linePoints.emplace_back(aPosition + Math::Vector2f{ aHalfExtents.x, -aHalfExtents.y });
        line.linePoints.emplace_back(aPosition - aHalfExtents);
    }
    void DebugDrawer::DrawSquareMinMax(Math::Vector2f aMinPosition, Math::Vector2f aMaxPosition, const Math::Color& aColor)
    {
        auto& line = DebugDrawer::Get().myLineCollection.emplace_back();
        line.color = aColor;

        line.linePoints.emplace_back(aMinPosition);
        line.linePoints.emplace_back(Math::Vector2f{ aMinPosition.x, aMaxPosition.y });

        line.linePoints.emplace_back(Math::Vector2f{ aMinPosition.x, aMaxPosition.y });
        line.linePoints.emplace_back(aMaxPosition);

        line.linePoints.emplace_back(aMaxPosition);
        line.linePoints.emplace_back(Math::Vector2f{ aMaxPosition.x, aMinPosition.y });

        line.linePoints.emplace_back(Math::Vector2f{ aMaxPosition.x, aMinPosition.y });
        line.linePoints.emplace_back(aMinPosition);
    }

    void DebugDrawer::DrawCircle(Math::Vector2f aPosition, float aRadius, unsigned aCircleResolution, const Math::Color& aColor)
    {
        float resRatio = TemporarySettingsSingleton::Get().GetResolutionRatio();

        auto& line = DebugDrawer::Get().myLineCollection.emplace_back();
        line.color = aColor;

        const float pi = 3.14159265358 * 2.f;
        float segmentSize = pi / aCircleResolution;

        for (int i = 0; i < aCircleResolution - 1; i++)
        {
            line.linePoints.emplace_back(aPosition + Math::Vector2f(cos(segmentSize * i) * resRatio, sin((segmentSize * i))) * aRadius * 0.5f);
            line.linePoints.emplace_back(aPosition + Math::Vector2f(cos(segmentSize * (i + 1)) * resRatio, sin(segmentSize * (i + 1))) * aRadius * 0.5f);
        }

        line.linePoints.emplace_back(aPosition + Math::Vector2f(cos(segmentSize * (aCircleResolution - 1)) * resRatio, sin((segmentSize * (aCircleResolution - 1)))) * aRadius * 0.5f);
        line.linePoints.emplace_back(aPosition + Math::Vector2f(cos(0) * resRatio, sin(0)) * aRadius * 0.5f);
    }
}