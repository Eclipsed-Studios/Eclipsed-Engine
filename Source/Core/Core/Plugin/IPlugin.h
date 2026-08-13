#pragma once

#include "Core/EngineContext.h"

namespace Eclipse::Core
{
	class IPlugin {
	public:
        ~IPlugin() = default;

	public:
        // Plugin lifecycle
        virtual bool Initialize(EngineContext& ctx) = 0;
        virtual void Shutdown() = 0;

        // Per-frame
        virtual void Update(float deltaTime) {}
        virtual void LateUpdate(float deltaTime) {}

        // Engine lifecycle
        virtual void OnEngineStart() {}
        virtual void OnEngineShutdown() {}

        // Editor support, if applicable
        virtual void OnEditorUpdate(float deltaTime) {}
	};
}