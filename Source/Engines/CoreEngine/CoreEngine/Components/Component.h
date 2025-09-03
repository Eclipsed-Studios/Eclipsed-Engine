#pragma once

#include "Interfaces/Serializable.h"

namespace ENGINE_NAMESPACE
{
    typedef unsigned GameObject;

    class Component : public ISerializable
    {
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

    public:
        virtual rapidjson::Value Save(rapidjson::Document::AllocatorType& allocator) const override;
        virtual void Load(const rapidjson::Value& aValue) override;

    public:
        GameObject gameObject;

    protected:
        unsigned myComponentID = 0;
        unsigned myComponentIndex = 0;

    private:
        static inline unsigned nextComponentID = 0;
    };
}