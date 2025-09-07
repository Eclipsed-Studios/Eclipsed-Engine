#include "PhysicsDebugDrawer.h"
#include "DebugDrawer.h"

#include "TemporarySettingsSingleton.h"

using namespace ENGINE_NAMESPACE;

void PhysicsDebugDrawer::DrawPolygon(const b2Vec2* vertices, int vertexCount, b2HexColor color, void* context)
{
    for (int i = 0; i < vertexCount - 1; i++)
    {
        int realIndexPOne = i == vertexCount - 1 ? 0 : i + 1;

        Math::Vector2f mathVertex0({ vertices[i].x, vertices[i].y });
        Math::Vector2f mathVertex1({ vertices[realIndexPOne].x, vertices[realIndexPOne].y });

        Math::Color mathColor(color);

        DebugDrawer::DrawLine(mathVertex0, mathVertex1, mathColor);
    }
}
void PhysicsDebugDrawer::DrawSolidPolygon(b2Transform transform, const b2Vec2* vertices, int vertexCount, float radius, b2HexColor color, void* context)
{
    float resRatio = TemporarySettingsSingleton::Get().GetResolutionRatio();

    Math::Vector2f position({ transform.p.x, transform.p.y });

    for (int i = 0; i < vertexCount; i++)
    {
        int realIndexPOne = i == vertexCount - 1 ? 0 : i + 1;

        Math::Vector2f mathVertex0(Math::Vector2f{ vertices[i].x, vertices[i].y });
        float vertX0 = mathVertex0.x * transform.q.c - mathVertex0.y * transform.q.s;
        float vertY0 = mathVertex0.x * transform.q.s + mathVertex0.y * transform.q.c;

        mathVertex0.x = vertX0;
        mathVertex0.y = vertY0;

        mathVertex0 += position;

        mathVertex0.x += 1;
        mathVertex0.x *= 0.5f;
        mathVertex0.y += 1;
        mathVertex0.y *= 0.5f;


        Math::Vector2f mathVertex1(Math::Vector2f{ vertices[realIndexPOne].x, vertices[realIndexPOne].y });
        float vertX1 = mathVertex1.x * transform.q.c - mathVertex1.y * transform.q.s;
        float vertY1 = mathVertex1.x * transform.q.s + mathVertex1.y * transform.q.c;

        mathVertex1.x = vertX1;
        mathVertex1.y = vertY1;

        mathVertex1 += position;

        mathVertex1.x += 1;
        mathVertex1.x *= 0.5f;
        mathVertex1.y += 1;
        mathVertex1.y *= 0.5f;

        Math::Color mathColor(color);
        mathColor.a = 1;

        DebugDrawer::DrawLine(mathVertex0, mathVertex1);
    }
}
void PhysicsDebugDrawer::DrawCircle(b2Vec2 center, float radius, b2HexColor color, void* context)
{
    DebugDrawer::DrawCircle(Math::Vector2f((center.x + 1.f) * 0.5f, (center.y + 1.f) * 0.5f), radius, 32);
}
void PhysicsDebugDrawer::DrawSolidCircle(b2Transform transform, float radius, b2HexColor color, void* context)
{

}
void PhysicsDebugDrawer::DrawSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color, void* context)
{

}
void PhysicsDebugDrawer::DrawTransform(b2Transform transform, void* context)
{

}

void PhysicsDebugDrawer::Init(b2DebugDraw* aDebugDraw)
{
    b2DebugDraw& derefDebugDraw = *aDebugDraw;

    // TODO: Hardcoded for now should be the cameras bounds in the future
    b2AABB aabb;
    {
        aabb.lowerBound = { -1000, -1000 };
        aabb.upperBound = { 1000, 1000 };
    }

    derefDebugDraw.drawingBounds = aabb;

    derefDebugDraw.drawShapes = true;

    derefDebugDraw.DrawPolygonFcn = &PhysicsDebugDrawer::DrawPolygon;
    derefDebugDraw.DrawSolidPolygonFcn = &PhysicsDebugDrawer::DrawSolidPolygon;

    derefDebugDraw.DrawCircleFcn = &PhysicsDebugDrawer::DrawCircle;
    derefDebugDraw.DrawSolidCircleFcn = &PhysicsDebugDrawer::DrawSolidCircle;

    derefDebugDraw.DrawSegmentFcn = &PhysicsDebugDrawer::DrawSegment;
    derefDebugDraw.DrawTransformFcn = &PhysicsDebugDrawer::DrawTransform;

    derefDebugDraw.context = nullptr;
}