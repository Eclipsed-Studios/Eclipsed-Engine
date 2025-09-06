#pragma once

#include <vector>
#include <utility>

#include "Math/Vector/Vector2.h"

namespace ENGINE_NAMESPACE
{
    class DebugDrawer
    {
    public:
        DebugDrawer() = default;
        ~DebugDrawer() = default;

        static DebugDrawer& Get()
        {
            static DebugDrawer instance;
            return instance;
        }

        void Init();
        void Render();

        static void DrawLine(Math::Vector2f aStart, Math::Vector2f aEnd);
        static void DrawRay(Math::Vector2f aStartPos, Math::Vector2f aDirection);

        static void DrawSquare(Math::Vector2f aPosition, Math::Vector2f aHalfExtents);
        static void DrawSquareMinMax(Math::Vector2f aMinPosition, Math::Vector2f aMaxPosition);

        static void DrawCircle(Math::Vector2f aPosition, float aRadius, unsigned aCircleResolution = 16);

    private:

        struct Line
        {
            std::vector<Math::Vector2f> linePoints;
        };

        std::vector<Line> myLineCollection;

        struct LineVTX
        {
            float posX;
            float posY;

            float trashDataX;
            float trashDataY;
        };

        std::vector<LineVTX> vertices;
        std::vector<unsigned> indices;

        unsigned myVTXbuffer;
        unsigned myIDXbuffer;
        unsigned myLineBuffer;

        unsigned pixelShaderID;
        unsigned vtxShaderID;
        unsigned programID;
    };
}
