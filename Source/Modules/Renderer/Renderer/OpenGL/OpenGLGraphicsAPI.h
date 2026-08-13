#pragma once

#include <vector>
#include <functional>

#include "OpenGLGraphicsBuffer.h"
#include "Core/ErrorCodes.h"

#include "Core/Math/Math.h"
#include "Core/Math/Color.h"

#include "UniformVariableManager.h"
#include "Renderer/GraphicsEngine.h"

#undef CreateWindow

struct GLFWwindow;
struct GLFWcursor;

namespace Eclipse
{
	class OpenGLGraphicsEngine : public GraphicsEngine
	{
	public:
		OpenGLGraphicsEngine() { myGraphicsBuffer = new OpenGLGraphicsBuffer(); }

		static inline unsigned gpuTimeQuery = 0;

		ErrorCode Init() override;
		void Render() override;


		void BeginFrame() override;
		void EndFrame() override;

		int ShouldWindowClose() override;

		Math::Vector2i GetWindowPosition() override;



		ErrorCode CheckErrorCodes(ErrorCode aErrorCode);

		void AddGlobalUniform(UniformType aType, const char* aUniformName, void* aValue);
		void UpdateGlobalUniform(UniformType aType, const char* aUniformName, void* aValue);
		void GetGlobalUniform(UniformType aType, const char* aUniformName, void* aValue);

		void SetUniform(UniformType aType, unsigned aShaderProgram, const char* aUniformName, void* aValue);

		void SetGlobalUniforms(unsigned aShaderProgram);

		void BindTexture(int aGLType, unsigned aTextureID);

		void BindFrameBuffer(unsigned aFrameBuffer);

		void ClearCurrentSceneBuffer(
			float aClearColorR,
			float aClearColorG,
			float aClearColorB,
			float aClearColorA = 1.f);

		void ClearCurrentSceneBuffer();

		void RegisterListenToResolutionChange(const std::function<void()>& aLambda);


		Math::Vector4ui ReadPixel(const Math::Vector2ui& aPos) override;

		void SetWindowIcon(const char* aPath);

		void CreateOpenGLTexture(unsigned& textureID, Math::Vector2f& spriteDivOne, float& dimDivOne, int channels, int width, int height, unsigned char* aPixels);
	private:
		GLFWwindow* myWindow = nullptr;
		UniformVariableManager myUniformManager;
		Math::Color myClearColor;

	private:
		ErrorCode InitOpenGL();
		ErrorCode CreateWindow();

	public:
		void SetCursor(MouseCursor aMouseCursor) override;
		void ResetCursor();
	private:

		static inline std::vector<GLFWcursor*> myMouseCursors;

		unsigned totalCount = 20;
		unsigned currentCount = 0;

		unsigned totaltimeElapsed = 0;
	};
}
