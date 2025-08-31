#pragma once

namespace ENGINE_NAMESPACE
{
    typedef unsigned GameObject;

    class Component
    {
        friend class ComponentManager;

    public:
        Component() = default;
        virtual ~Component() = default;

        void SetComponentID() { myComponentID = ++nextComponentID; }

        virtual void Awake() {}
        virtual void Start() {}

        virtual void EarlyUpdate() {}
        virtual void Update() {}
        virtual void LateUpdate() {}

        GameObject gameObject;

    protected:
        unsigned myComponentID = 0;
        unsigned myComponentIndex = 0;

    private:
        static inline unsigned nextComponentID = 0;
    };
}