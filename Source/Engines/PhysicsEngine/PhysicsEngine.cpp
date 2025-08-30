#include "PhysicsEngine.h"

#include "Timer.h"

#include "box2d/box2d.h"

namespace ENGINE_NAMESPACE
{
    b2BodyId *PhysicsEngine::CreateRigidBody(const Math::Vector2f &aStartPosition)
    {
        auto &body = myBodies.emplace_back();
        b2BodyDef bodyDefine = b2DefaultBodyDef();
        bodyDefine.position = b2Vec2(aStartPosition.x, aStartPosition.y);
        body = b2CreateBody(myWorld, &bodyDefine);

        return &body;
    }

    void PhysicsEngine::Init()
    {
        {
            b2WorldDef worldDef;
            worldDef = b2DefaultWorldDef();
            worldDef.gravity = b2Vec2(myGravity.x, myGravity.y);
            myWorld = b2CreateWorld(&worldDef);
        }

        // {
        //     auto &body = myBodies.emplace_back();
        //     b2BodyDef groundBodyDef = b2DefaultBodyDef();
        //     groundBodyDef.position = b2Vec2(0, -100);
        //     body = b2CreateBody(myWorld, &groundBodyDef);

        //     b2Polygon groundBox = b2MakeBox(50.f, 10.f);
        //     b2ShapeDef groundShapeDef = b2DefaultShapeDef();
        //     b2CreatePolygonShape(body, &groundShapeDef, &groundBox);
        // }

        // {
        //     auto &body = myBodies.emplace_back();
        //     b2BodyDef bodyDef = b2DefaultBodyDef();
        //     bodyDef.type = b2_dynamicBody;
        //     bodyDef.position = b2Vec2(0.0f, 0.0f);
        //     body = b2CreateBody(myWorld, &bodyDef);

        //     b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
        //     b2ShapeDef shapeDef = b2DefaultShapeDef();
        //     shapeDef.density = 1.0f;
        //     shapeDef.material.friction = 0.3f;

        //     b2CreatePolygonShape(body, &shapeDef, &dynamicBox);
        // }
    }

    void PhysicsEngine::Update()
    {
        b2World_Step(myWorld, Time::GetDeltaTime(), substepCount);
    }
}