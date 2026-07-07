#pragma once

#include "CoreEngine/ErrorCodes.h"

#include "CoreEngine/Math/Vector/Vector2.h"
#include "CoreEngine/Math/Vector/Vector4.h"

namespace Eclipse
{
    class BaseGraphicsBuffer;
    class OpenGLGraphicsBuffer;

    class GraphicsEngine
    {
    public:
        GraphicsEngine() = default;
        virtual ~GraphicsEngine() = default;

        template <class T>
        static void InitSpecifiedAPI();

        template<class T>
        static T* Get() { return reinterpret_cast<T*>(Instance); }

        static GraphicsEngine* Get() { return Instance; }
        
        virtual ErrorCode Init() = 0;
        virtual void Render() = 0;

        virtual void BeginFrame() = 0;
        virtual void EndFrame() = 0;

        virtual int ShouldWindowClose() = 0;

        virtual Math::Vector2i GetWindowPosition() = 0;

        virtual Math::Vector4ui ReadPixel(const Math::Vector2ui& aPos) = 0;

        BaseGraphicsBuffer* GetGraphicsBuffer() { return myGraphicsBuffer; }
        
    public:
        enum class MouseCursor {
            Hand,
            Grab
        };

        virtual void SetCursor(MouseCursor aMouseCursor) {}
        
        BaseGraphicsBuffer* myGraphicsBuffer;
        
        static inline GraphicsEngine* Instance;
    };

    template <class T>
    void GraphicsEngine::InitSpecifiedAPI()
    {
        Instance = new T();
    }
}
