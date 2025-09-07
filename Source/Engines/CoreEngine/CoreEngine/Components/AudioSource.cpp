#include "AudioSource.h"

#include "Editor/ImGui/ImGui_Impl.h"

#include <sstream>

namespace ENGINE_NAMESPACE
{
	// THIS IS WRONG.
	// AS OF NOW THE AUDIO CLIP STORES THE CHANNEL.
	// BUT THE SOURCE NEEDS TO STORE THE CHANNEL. 
	// SINCE WE CAN HAVE MULTIPLE SOURCES WITH THE SAME SOUND BUT DIFFERENT VOLUMES AND OTHER DATA.

	void AudioSource::SetAudioClip(const char* aPath)
	{
		myAudioClip = Resources::Get<AudioClip>(aPath);
	}

	void AudioSource::SetVolume(float aVolume)
	{
		myVolume = aVolume;
		myAudioClip->myChannel->setVolume(aVolume);
	}

	void AudioSource::Play()
	{
		if (!myIsPlaying)
		{
			AudioManager::PlayAudio(*myAudioClip.Get());
			
			SetVolume(myVolume);
			SetLooping(myIsLooping);

			myIsPlaying = true;
		}
		else if (myIsPaused)
		{
			myIsPaused = !myIsPaused;
			myAudioClip->myChannel->setPaused(myIsPaused);
		}
	}

	void AudioSource::Pause()
	{
		myIsPaused = true;
		myAudioClip->myChannel->setPaused(true);
	}

	void AudioSource::Stop()
	{
		myAudioClip->myChannel->stop();
		myAudioClip->myChannel = nullptr;

		myIsPlaying = false;
	}

	void AudioSource::SetLooping(bool aState)
	{
		myIsLooping = aState;

		if (!myAudioClip && !myAudioClip->myChannel)  return;

		if (aState) // Play infinitely looping
		{
			myAudioClip->myChannel->setMode(FMOD_LOOP_NORMAL);
			myAudioClip->myChannel->setLoopCount(-1);
		}
		else // Play once
		{
			myAudioClip->myChannel->setMode(FMOD_LOOP_OFF);
			myAudioClip->myChannel->setLoopCount(0);
		}
	}

	void AudioSource::DrawInspector()
	{
		Editor::ImGui_Impl::DrawComponentHeader("AudioSource", myInspectorWasDrawn);
		if (!myInspectorWasDrawn) return;

		std::stringstream ss;
		ss << "##" << this;

		if (!myAudioClip)
		{
			ImGui::Text("No audio clip");
		}

		ImGui::Button("Drop here");
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_DND"))
			{
				std::string path;
				path.resize(payload->DataSize);

				memcpy(path.data(), payload->Data, payload->DataSize);
				SetAudioClip(path.c_str());

			}
			ImGui::EndDragDropTarget();
		}

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



		{ // Volume
			ImGui::Text("Volume");
			ImGui::SameLine();
			if (ImGui::SliderFloat(("##Volume" + ss.str()).c_str(), &myVolume, 0.f, 1.f))
			{
				SetVolume(myVolume);
			}
		}

		{ // Looping
			ImGui::Text("Is Looping");
			ImGui::SameLine();
			if (ImGui::Checkbox(("##IsLooping" + ss.str()).c_str(), &myIsLooping))
			{
				SetLooping(myIsLooping);
			}
		}
	}
}