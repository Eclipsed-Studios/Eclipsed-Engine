#pragma once

#include "Interfaces/Serializable.h"

namespace ENGINE_NAMESPACE
{
    typedef unsigned RegisteredTypeIndex;
    typedef unsigned GameObject;

    namespace Editor
    {
        class InspectorWindow;

    }

    class Component : public ISerializable
    {
        friend class Editor::InspectorWindow;

        friend class ComponentManager;
        friend class SceneLoader;

    public:
        Component() = default;
        virtual ~Component() = default;

        void SetComponentID() { myComponentID = ++nextComponentID; }

    public:
        virtual void Awake() {}
        virtual void Start() {}

        virtual void EarlyUpdate() {}
        virtual void Update() {}
        virtual void LateUpdate() {}

        virtual void OnCollisionEnter() {}
        virtual void OnCollisionExit() {}

        virtual void OnDrawGizmos() {}

    protected:
        virtual void DrawInspector();

    public:
        virtual rapidjson::Value Save(rapidjson::Document::AllocatorType& allocator) const override;
        virtual void Load(const rapidjson::Value& aValue) override;

    public:
        GameObject gameObject;

    protected:
        // Higher number higher priority
        unsigned myUpdateStartPriority = 0;

        unsigned myComponentID = 0;
        unsigned myComponentIndex = 0;

    private:
        RegisteredTypeIndex myUniqueComponentID;
        static inline unsigned nextComponentID = 0;

    protected:
        // IFDEF EDITOR
        bool myInspectorWasDrawn = false;
    };
}