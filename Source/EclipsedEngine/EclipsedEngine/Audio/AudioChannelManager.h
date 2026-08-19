#pragma once

#include "IAudioChannelGroup.h"

#include <string>
#include <unordered_map>

namespace Eclipse::Audio
{
	class AudioChannelManager
	{
	public:
		static void Init();
		static IAudioChannelGroup* CreateChannelGroup(const char* channelName);
		static IAudioChannelGroup* GetChannelGroup(const char* channelName);

	private:
		static std::unordered_map<std::string, IAudioChannelGroup*> channels;
	};
}