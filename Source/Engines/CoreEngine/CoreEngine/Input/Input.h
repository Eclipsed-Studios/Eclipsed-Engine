#pragma once

#include <bitset>

#include "Math/Vector/Vector2.h"
#include "Keycodes.h"

struct GLFWwindow;
namespace ENGINE_NAMESPACE
{
#define MAX_KEYS 512

	class Input
	{
	public:
		static bool GetKey(char aKey);
		static bool GetKey(int aKey);
		static bool GetKey(Keycode aKey);

		static bool GetKeyDown(char aKey);
		static bool GetKeyDown(int aKey);
		static bool GetKeyDown(Keycode aKey);

		static bool GetKeyUp(char aKey);
		static bool GetKeyUp(int aKey);
		static bool GetKeyUp(Keycode aKey);

		static bool GetAny();
		static Keycode GetAnyKey();
		
		static bool GetMouse(int aKey);
		static bool GetMouse(MouseButton aKey);

		static bool GetMouseDown(int aKey);
		static bool GetMouseDown(MouseButton aKey);

		static bool GetMouseUp(int aKey);
		static bool GetMouseUp(MouseButton aKey);


		static const Math::Vector2i& GetMousePos();
		static const Math::Vector2i& GetMouseDeltaPos();

		static const Math::Vector2i& GetScroll();
		static const Math::Vector2i& GetNormalizedScroll();


		static bool IsWindowFocused();
		static bool IsMouseInside();

	public:
		static void Init();
		static void Update();

	private:
		static void OnKey_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void OnMousePos_Callback(GLFWwindow* window, double x, double y);
		static void OnMouseEnter_Callback(GLFWwindow* window, int entered);
		static void OnMouseButton_Callback(GLFWwindow* window, int button, int action, int mods);
		static void OnWindowFocus_Callback(GLFWwindow* window, int focused);
		static void OnMouseScroll_Callback(GLFWwindow* window, double xOffset, double yOffset);

	private:
		static inline std::bitset<MAX_KEYS> zeroKeys;

		static inline std::bitset<MAX_KEYS> currentKeys;
		static inline std::bitset<MAX_KEYS> lastKeys;

		static inline std::bitset<MAX_KEYS> pressedThisFrame;
		static inline std::bitset<MAX_KEYS> releasedThisFrame;

		static inline Math::Vector2i currentPos;
		static inline Math::Vector2i lastPos;
		static inline Math::Vector2i mouseDeltaPos;

		static inline Math::Vector2i mouseScrollDelta;
		static inline Math::Vector2i normalizedMouseScrollDelta;

		static inline bool mouseIsInside;
		static inline bool windowFocused;
	};
}