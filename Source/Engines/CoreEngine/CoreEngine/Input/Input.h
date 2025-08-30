#pragma once

#include <bitset>

struct GLFWwindow;
namespace ENGINE_NAMESPACE
{
#define MAX_KEYS 512

	class Input
	{
	public:
		static bool GetKey(char aKey);
		static bool GetKeyDown(char aKey);
		static bool GetKeyUp(char aKey);

		static void Init();
		static void Update();

	private:
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	private:
		static inline std::bitset<MAX_KEYS> myCurrentKeys;
		static inline std::bitset<MAX_KEYS> myLastKeys;

		static inline std::bitset<MAX_KEYS> myPressedThisFrame;
		static inline std::bitset<MAX_KEYS> myReleasedThisFrame;
	};
}