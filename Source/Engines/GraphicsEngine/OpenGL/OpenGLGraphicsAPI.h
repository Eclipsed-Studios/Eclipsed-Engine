#pragma once

#include "ErrorCodes.h"

#include <vector>
#include "Math/Math.h"

#include "UniformVariableManager.h"

#include "Math/Color.h"

#include <functional>

#undef CreateWindow

struct GLFWwindow;

namespace Eclipse
{
	class GraphicsEngine
	{
	public:
		static ErrorCode Init();
		static void BeginFrame();
		static void Render();
		static void EndFrame();

		static int ShouldWindowClose();

		static ErrorCode CheckErrorCodes(ErrorCode aErrorCode);

		static void AddGlobalUniform(UniformType aType, const std::string& aUniformName, void* aValue);
		static void UpdateGlobalUniform(UniformType aType, const std::string& aUniformName, void* aValue);
		static void GetGlobalUniform(UniformType aType, const std::string& aUniformName, void* aValue);

		static void SetGlobalUniforms(unsigned aShaderProgram);

		static void BindTexture(int aGLType, unsigned aTextureID);

		static void BindFrameBuffer(unsigned aFrameBuffer);

		static void ClearCurrentSceneBuffer(
        float aClearColorR = myClearColor.r, 
        float aClearColorG = myClearColor.g, 
        float aClearColorB = myClearColor.b);

		static void RegisterListenToResolutionChange(const std::function<void()>& aLambda);

	private:
		static inline GLFWwindow* myWindow;
		static inline UniformVariableManager myUniformManager;
		static inline Math::Color myClearColor;

	private:
		static ErrorCode InitOpenGL();
		static ErrorCode CreateWindow();
	};
}
