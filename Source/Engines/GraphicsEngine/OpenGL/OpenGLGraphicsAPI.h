#pragma once

#include "ErrorCodes.h"

struct GLFWwindow;

namespace ENGINE_NAMESPACE
{
	class GraphicsEngine
	{
	public:
		static  ErrorCode Init();
		static void BeginFrame();
		static void Render();
		static void EndFrame();

		static int ShouldWindowClose();

		static ErrorCode CheckErrorCodes(ErrorCode aErrorCode);

	private:
		static inline GLFWwindow* myWindow;

	private:
		static ErrorCode InitOpenGL();
		static ErrorCode CreateWindow();
	};
}
