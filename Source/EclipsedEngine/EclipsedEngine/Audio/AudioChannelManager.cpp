#include "AudioChannelManager.h"

#include "EclipsedEngine/Core/MainSingleton.h"

namespace Eclipse::Audio
{
	std::unordered_map<std::string, IAudioChannelGroup*> AudioChannelManager::channels;


	void AudioChannelManager::Init()
	{

	}

	IAudioChannelGroup* AudioChannelManager::CreateChannelGroup(const char* channelName)
	{
		return nullptr;
	}

	IAudioChannelGroup* AudioChannelManager::GetChannelGroup(const char* channelName)
	{
		return nullptr;
	}

}