#include "AudioSource.h"

#include "Editor/ImGui/ImGui_Impl.h"
#include "Editor/DragAndDrop.h"
#include <sstream>

namespace Eclipse
{
	void AudioSource::Awake()
	{
		SetAudioClip(myAudioPath->c_str());
	}

	void AudioSource::SetAudioClip(const char* aPath)
	{
		myAudioClip = Resources::Get<AudioClip>(aPath);
		myAudioPath = aPath;
	}

	void AudioSource::SetVolume(float aVolume)
	{
		myVolume = aVolume;
		myChannel->setVolume(aVolume);
	}

	void AudioSource::Play()
	{
		if (!myIsPlaying)
		{
			AudioManager::PlayAudio(*myAudioClip.Get(), &myChannel);
			
			SetVolume(myVolume);
			SetLooping(myIsLooping);

			myIsPlaying = true;
		}
		else if (myIsPaused)
		{
			myIsPaused = !myIsPaused;
			myChannel->setPaused(myIsPaused);
		}
	}

	void AudioSource::Pause()
	{
		myIsPaused = true;
		myChannel->setPaused(true);
	}

	void AudioSource::Stop()
	{
		myChannel->stop();
		myChannel = nullptr;

		myIsPlaying = false;
	}

	void AudioSource::SetLooping(bool aState)
	{
		myIsLooping = aState;

		if (!myAudioClip && !myChannel)  return;

		if (aState) // Play infinitely looping
		{
			myChannel->setMode(FMOD_LOOP_NORMAL);
			myChannel->setLoopCount(-1);
		}
		else // Play once
		{
			myChannel->setMode(FMOD_LOOP_OFF);
			myChannel->setLoopCount(0);
		}
	}

	void AudioSource::DrawInspector()
	{
		std::stringstream ss;
		ss << "##" << this;

		bool hasAudioClip = myAudioClip;


		Editor::DragAndDrop::TextBox(hasAudioClip ? myAudioClip->GetRelativePath() : "No audio clip", {5, 5}, {0,0,0,0}, {255, 255,255, 1}, "audioClipDND");

		if (ImGui::BeginDragDropTarget())
		{
			int idx = (int)Editor::DragAndDrop::AssetDragAndDropIdx::Audio;
			const char* dndString = Editor::DragAndDrop::dragAndDropString[idx];

			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(dndString))
			{
				std::string path;
				path.resize(payload->DataSize);

				memcpy(path.data(), payload->Data, payload->DataSize);
				SetAudioClip(path.c_str());

			}
			ImGui::EndDragDropTarget();
		}

		if (!hasAudioClip) return;

		if (!myIsPlaying && ImGui::Button("Play"))
		{
			Play();
		}
		else if (myIsPlaying)
		{
			if (myIsPaused)
			{
				if (ImGui::Button("Start"))
				{
					Play();
				}
			}
			else
			{
				if (ImGui::Button("Pause"))
				{
					Pause();
				}
			}

			ImGui::SameLine();

			if (ImGui::Button("Stop"))
			{
				Stop();
			}
		}
	}
}