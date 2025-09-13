#pragma once

#include "Collider2D.h"

#include <Math/Vector/Vector2.h>
#include "ECS/ComponentManager.h"
#include "Reflection/ReflectionDefines.h"

namespace Eclipse
{
    class CapsuleCollider2D : public Collider2D
    {
        BASE_SELECTION(CapsuleCollider2D, Collider2D, 5)

    public:
        void Awake() override;

        void OnTransformDirty();

        void SetRadius(float aRadius);
        void SetHalfHeight(float aHalfHeight);

    protected:
        void DrawInspector() override;

    private:
        ReflectedVar(float, myRadius);
        ReflectedVar(float, myHalfHeight);

        ReflectedVar(float, myRealRadius);
        ReflectedVar(float, myRealHalfHeight);

        class Transform2D* myTransform;
    };
}