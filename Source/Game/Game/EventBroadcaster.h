#pragma once

#include "Interactable.h"
#include "Assets/Assets/TextureAsset.h"

#include <string>

class EventBroadcaster
{
public:
	static void Broadcast(std::string evetnName);
	static bool Listen(std::string eventName);
	static void Clear();

private:
	static inline std::vector<std::string> events;
};