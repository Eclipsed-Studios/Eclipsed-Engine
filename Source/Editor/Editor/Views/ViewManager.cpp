#include "ViewManager.h"

#include "AbstractView.h"
#include "ViewRegistry.h"
#include "ImGui/imgui.h"

namespace Eclipse::Editor
{
	std::vector<AbstractView*> ViewManager::views;

	void ViewManager::Init()
	{
		AbstractView* view = ViewRegistry::GetView("AssetBrowserView");
		views.push_back(view->GetNew());
	}

	void ViewManager::Update()
	{
		for (int i = 0; i < (int)views.size(); i++)
		{
			AbstractView* view = views[i];

			ImGui::Begin(view->GetName(), view->GetIsOpenPtr(), view->GetFlags());
			view->PreUpdate();
			view->Update();
			view->PostUpdate();
			ImGui::End();
		}

	}
}