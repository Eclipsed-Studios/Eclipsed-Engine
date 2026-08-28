#include "AudioEmitter.h"

#include "Audio/AudioManager.h"
#include "EclipsedEngine/Components/Transform2D.h"
#include "EclipsedEngine/Components/Audio/AudioListener.h"



#include "EclipsedEngine/Editor/ComponentInspectorDrawer.h"


namespace Eclipse
{
	void AudioEmitter::Awake()
	{
		InitAudio();

		if (playOnAwake) {
			Play();
		}

		Transform2D* trans = gameObject->transform;
		trans->AddFunctionToRunOnDirtyUpdate(this,
			[this]() {
				this->UpdateAudioPosition();
			}
		);
	}

	void AudioEmitter::OnDestroy() {
		channel->stop();
	}

	void AudioEmitter::Update()
	{
		SetVolume(volume);
		SetSpatialMode(EnableSpatial);
	}

	void AudioEmitter::SetSpatialMode(bool is3D)
	{
		channel->setMode(is3D ? FMOD_3D : FMOD_2D);
	}

	void AudioEmitter::Play() {
		AudioManager::PlayAudio(audioClip->dataPtr->sound, &channel);

		InitAudio();

		isPlaying = true;

		UpdateAudioPosition();
		SetSpatialMode(EnableSpatial);
		SetVolume(volume);

		channel->setPaused(false);
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

		InitAudio();
	}

	void AudioEmitter::Stop() {
		channel->stop();
	}

	void AudioEmitter::SetVolume(float aVolume)
	{
		AudioListener* listener = AudioListener::GetListener();
		if (!listener)
			return;

		float audioAttenuation = 1.f;
		if (EnableSpatial && listener != nullptr)
		{
			channel->setMode(
				FMOD_3D |
				FMOD_3D_WORLDRELATIVE |
				FMOD_3D_INVERSEROLLOFF
			);

			Math::Vector2f p = gameObject->transform->GetPosition();
			Math::Vector2f l = listener->gameObject->transform->GetPosition();

			float dx = p.x - l.x;
			float dy = p.y - l.y;

			float dist = sqrt(dx * dx + dy * dy);

			float t = dist / 20.f;
			t = std::clamp(t, 0.0f, 1.0f);

			audioAttenuation = 1.0f - (t * t * (3.0f - 2.0f * t));
		}
		else
		{
			channel->setMode(
				FMOD_2D
			);
		}

		volume = aVolume;
		channel->setVolume(audioAttenuation * volume);
	}

	float AudioEmitter::GetVolume() const {
		return volume;
	}

	void AudioEmitter::InitAudio()
	{
		channel->setChannelGroup(AudioManager::GetBus(AudioBus::Master));

		channel->setMode(
			FMOD_3D |
			FMOD_3D_WORLDRELATIVE |
			FMOD_3D_INVERSEROLLOFF
		);

		channel->set3DMinMaxDistance(2.0f, 5.f);
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


#ifdef ECL_EDITOR

#include "Assets/Core/AssetDatabase.h"
#include "Core/Files/FileInfo.h"
#include "EclipsedEngine/Editor/Common/DragAndDrop.h"

namespace Eclipse::Editor
{
	void DrawInspector(AudioEmitter* comp)
	{
		ImGui::Text("Volume");
		ImGui::SameLine();
		float volume = comp->GetVolume() * 100.f;
		if (ImGui::SliderFloat(("##audio_volume" + std::to_string(comp->myInstanceComponentID)).c_str(), &volume, 0.f, 100.f))
		{
			volume /= 100.f;
			comp->SetVolume(volume);
		}

		ImGui::Text("Clip");
		ImGui::SameLine();

		std::string name = "No material.";

		Assets::AudioClip& audio = comp->audioClip.Get();
		if (audio.IsValid())
		{
			name = MainSingleton::GetInstance<Assets::AssetDatabase>().GetProcessedFile(audio.GetAssetID()).fileName;
		}

		if (Editor::DragAndDrop::BeginTarget(name.c_str(), Utilities::FileInfo::FileType_Audio))
		{
			comp->SetAudioClip(Assets::AssetManager::Load<Assets::AudioClip>(
				MainSingleton::GetInstance<Assets::AssetDatabase>().GetProcessedFile(Editor::DragAndDrop::payloadBuffer).guid)
			);
		}







		ImGui::Text("Look here this is the way.");
	}

	//REGISTER_INSPECTOR(AudioEmitter);
}
#endif