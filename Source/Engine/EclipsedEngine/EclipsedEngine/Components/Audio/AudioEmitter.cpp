#include "AudioEmitter.h"

#include "AudioEngine/AudioManager.h"
#include "EclipsedEngine/Components/Transform2D.h"
#include "EclipsedEngine/Components/Audio/AudioListener.h"


namespace Eclipse
{
	void AudioEmitter::Awake()
	{
		if (playOnAwake) {
			Play();
		}
	}

	void AudioEmitter::OnDestroy() {
		channel->stop();
	}

	void AudioEmitter::Update()
	{
		SetVolume(volume);
	}

	void AudioEmitter::SetSpatialMode(bool is3D)
	{
		channel->setMode(is3D ? FMOD_3D : FMOD_2D);
	}

	void AudioEmitter::Play() {
		isPlaying = true;
		channel->setPaused(isPlaying);
		AudioManager::PlayAudio(audioClip->dataPtr->sound, &channel);

		SetSpatialMode(EnableSpatial);

		Transform2D* trans = gameObject->transform;
		trans->AddFunctionToRunOnDirtyUpdate(this,
			[this]() {
				this->UpdateAudioPosition();
			}
		);

		UpdateAudioPosition();
	}

	void AudioEmitter::Resume() {
		isPlaying = true;
		channel->setPaused(false);
	}

	void AudioEmitter::Pause() {
		isPlaying = false;
		channel->setPaused(true);
	}

	void AudioEmitter::SetAudioClip(Assets::AudioClip clip)
	{
		audioClip = clip;

		channel->setMode(
			FMOD_3D | 
			FMOD_3D_WORLDRELATIVE | 
			FMOD_3D_INVERSEROLLOFF
		);

		channel->set3DMinMaxDistance(2.0f, 5.f);
	}

	void AudioEmitter::Stop() {
		channel->stop();
	}

	void AudioEmitter::SetVolume(float aVolume) {
		AudioListener* listener = AudioListener::GetListener();

		Math::Vector2f p = gameObject->transform->GetPosition();
		Math::Vector2f l = listener->gameObject->transform->GetPosition();

		float dx = p.x - l.x;
		float dy = p.y - l.y;

		float dist = sqrt(dx * dx + dy * dy);

		float t = dist / 20.f;   
		t = std::clamp(t, 0.0f, 1.0f);

		float v = 1.0f - (t * t * (3.0f - 2.0f * t));

		volume = aVolume;
		channel->setVolume(v*volume);
	}

	float AudioEmitter::GetVolume() const {
		return volume;
	}

	void AudioEmitter::UpdateAudioPosition()
	{
		Transform2D* trans = gameObject->transform;
		Math::Vector2f ePos = trans->GetPosition();

		FMOD_VECTOR pos = { ePos.x, ePos.y, 1.f };
		FMOD_VECTOR vel = { 0.f, 0.f, 0.f };

		channel->set3DAttributes(&pos, &vel);
	}
}