#pragma once

namespace Eclipse::Audio
{
	class IAudioDevice;
	class IAudioManager
	{
	public:
		virtual void Init() = 0;
		virtual void Update() = 0;

		IAudioDevice* GetDevice();

	public:
		IAudioDevice* audioDevice;
	};
}