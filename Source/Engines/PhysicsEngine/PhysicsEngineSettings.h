#pragma once

enum Box2DBodyType
{
    StaticBody = 0,
    KinematicBody = 1,
    DynamicBody = 2
};

struct RigidBodySettings
{
    Box2DBodyType BodyType = StaticBody;

    bool LockRotation = false;
    bool LockXPos = false;
    bool LockYPos = false;
};

struct RigidBodyUserData
{
    unsigned gameobject = 0;
    unsigned componentIndexID = 0;
};