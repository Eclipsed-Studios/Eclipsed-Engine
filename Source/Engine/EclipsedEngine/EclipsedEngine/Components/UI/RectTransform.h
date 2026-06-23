#pragma once

#include "EntityEngine/ComponentManager.h"
#include "EclipsedEngine/Components/Component.h"

ECLIPSED_CLASS;

namespace Eclipse
{
    class RectTransform : public Component
    {
        COMPONENT_BASE_2(RectTransform, UINT_MAX * 0.5f)

    private:
        void UpdateTransforms();
        void DirtyUpdate();

        void AddParentPosition(GameObject* aParent, Math::Vector2f& aPosition) const;
        
    public:
        void EditorUpdate() override;

        
        Math::Vector2f GetPosition() const;
        Math::Vector2f GetLocalPosition();
        
        void SetPosition(const Math::Vector2f& aPosition);

        void AddFunctionToRunOnDirtyUpdate(const std::function<void()>& aFunction);
        
        //void RectTransform::AddParentScale(GameObject* aParent, Math::Vector2f& aPosition) const;

    public:
        Math::Vector2f Position = Math::Vector2f(0, 0);
        Math::Vector2f WidthHeightPX = Math::Vector2f(100, 100);

        bool ScaleWithCanvasX = false;
        bool ScaleWithCanvasY = false;

        bool AlignLeft = false;
        bool AlignTop = false;
        bool AlignRight = false;
        bool AlignBottom = false;

        Math::Vector2f GlobalPosition;
        
        Math::Vector2f lastPosition;
        Math::Vector2f lastWidthHeightPX;
        
        class Canvas* myCanvas;

        std::vector<std::function<void()>> myFunctionsToRunOnDirtyUpdate;

        bool myIsDirty = false;
    };
}