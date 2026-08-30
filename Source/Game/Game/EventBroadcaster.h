#pragma once

#include "Interactable.h"
#include "Assets/Assets/TextureAsset.h"

#include <string>

class EventBroadcaster
{
public:
	static void Broadcast(const std::string& evetnName);
	static bool Listen(const std::string& eventName);
	static void DeleteEvent(const std::string& eventName);
	static void Clear();

private:
	static inline std::vector<std::string> events;
};