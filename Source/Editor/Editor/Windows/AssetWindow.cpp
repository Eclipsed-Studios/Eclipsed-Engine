#include "AssetWindow.h"

#include "ImGui/imgui.h"
#include "ECS/ComponentManager.h"


namespace ENGINE_NAMESPACE::Editor
{
	AssetWindow::AssetWindow(const int& aId)
	{
		myWindowName = "Assets";
		myID = aId == -1 ? Random::GetValue<int>() : aId;

		myCurrentPath = ASSET_PATH;
	}

	void AssetWindow::Open()
	{
	}
	
	void AssetWindow::Update()
	{
		using namespace std::filesystem;
		for (const directory_entry& entry : recursive_directory_iterator(myCurrentPath))
		{
			ImGui::Text(entry.path().string().c_str());
		}
	}
	
	void AssetWindow::Close()
	{
	}
}