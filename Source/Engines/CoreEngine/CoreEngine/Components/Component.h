#pragma once

namespace ENGINE_NAMESPACE
{
    typedef unsigned GameObject;

    class Component
    {
    public:
        Component() = default;
        ~Component() = default;

        void SetComponentID() { myComponentID = ++nextComponentID; }

        virtual void Awake() {}
        virtual void Start() {}

        virtual void EarlyUpdate() {}
        virtual void Update() {}
        virtual void LateUpdate() {}

        GameObject gameObject;

    private:
        static inline unsigned nextComponentID = 0;
        unsigned myComponentID = 0;
    };
}