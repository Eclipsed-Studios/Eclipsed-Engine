#include "InspectorWindow.h"

#include "Editor/DragAndDrop.h"

#include "Components/AudioSource.h"
#include "Components/Rendering/SpriteRenderer2D.h"

namespace Eclipse
{
	void AudioSource::DrawInspector()
	{
		std::stringstream ss;
		ss << "##" << this;

		bool hasAudioClip = myAudioClip;


		if (Editor::DragAndDrop::BeginTarget(hasAudioClip ? myAudioClip->GetRelativePath() : "No audio clip", FileInfo::FileType_Audio))
		{
			myAudioPath = Editor::DragAndDrop::payloadBuffer;
			SetAudioClip(myAudioPath->c_str());
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




	void SpriteRenderer2D::DrawInspector()
	{
		if (Editor::DragAndDrop::BeginTarget(hasTexture ?  std::filesystem::relative(myTexturePath->c_str(), ASSET_PATH).string().c_str() : "No texture clip", FileInfo::FileType_Texture))
		{
			myTexturePath = Editor::DragAndDrop::payloadBuffer;
			SetTexture(myTexturePath->c_str());
		}
	}
}