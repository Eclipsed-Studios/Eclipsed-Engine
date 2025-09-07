#pragma once

#include "ErrorCodes.h"

#include <vector>
#include "Math/Math.h"

#include "UniformVariableManager.h"

struct GLFWwindow;

namespace ENGINE_NAMESPACE
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

		static void SetGlobalUniforms(unsigned aShaderProgram);

	private:
		static inline GLFWwindow* myWindow;

		static inline UniformVariableManager myUniformManager;

	private:
		static ErrorCode InitOpenGL();
		static ErrorCode CreateWindow();
	};
}
