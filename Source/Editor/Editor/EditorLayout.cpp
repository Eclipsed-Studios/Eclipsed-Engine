#include "EditorLayout.h"

#include "Views/Types/AssetBrowserView.h"
#include "Views/Types/InspectorView.h"

#include <regex>
#include "ImGui/imgui.h"
#include "EclipsedEngine/Core/Settings/EditorSettings.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

namespace Eclipse::Editor
{
	void EditorLayout::Init()
	{
		EditorLayout::RegisterViewTypes();

	}

	void EditorLayout::EndFrame()
	{

	}

	void EditorLayout::Draw()
	{
		// Clear views to close.
		for (auto it = activeViews.begin(); it < activeViews.end();)
		{
			EditorViewInstance* instance = *it;

			if (!instance->open)
			{
				ImGui::ClearWindowSettings(instance->idString.c_str());

				delete instance;
				it = activeViews.erase(it);
				continue;
			}

			++it;
		}

		Internal_OpenLayout();

		ImGui::DockSpaceOverViewport(
			1,
			ImGui::GetMainViewport(),
			ImGuiDockNodeFlags_PassthruCentralNode
		);

		for (auto instance : activeViews)
		{
			std::string windowName = std::string(instance->view->GetName()) + "##" + std::to_string(instance->id);

			if (ImGui::Begin(windowName.c_str(), &instance->open))
			{
				instance->view->Draw();
			}
			ImGui::End();
		}
	}

	void EditorLayout::OpenLayout(std::string_view layoutName)
	{
		layoutNameToopen = layoutName;
	}

	void EditorLayout::RegisterViewTypes()
	{
		registry.RegisterView<AssetBrowserView>();
		registry.RegisterView<InspectorView>();
	}

	void EditorLayout::OpenView(std::string_view viewName, int id)
	{
		const EditorViewType* type = registry.GetViewType(viewName);
		if (!type) return;

		EditorViewInstance* instance = type->create(id);
		activeViews.push_back(instance);
	}

	EditorViewRegistry& EditorLayout::GetViewRegistry()
	{
		return registry;
	}

	

	void EditorLayout::Internal_OpenLayout()
	{
		if (!layoutNameToopen.empty())
		{
			for (EditorViewInstance* instance : activeViews)
			{
				ImGui::ClearWindowSettings(instance->idString.c_str());
				delete instance;
			}

			activeViews.clear();

			std::string path = (PathManager::GetProjectPath() / "Editor/Layouts" / layoutNameToopen).generic_string() + ".layout";
			std::filesystem::copy_file(
				path,
				"CurrentLayout.layout",
				std::filesystem::copy_options::overwrite_existing
			);

			std::ifstream file("CurrentLayout.layout", std::ios::binary);
			std::string content = {
				std::istreambuf_iterator<char>(file),
				std::istreambuf_iterator<char>()
			};

			std::regex pattern(R"(\[Window\]\[([^#]*)(?:##(.*))?\])");
			for (std::sregex_iterator it(content.begin(), content.end(), pattern);
				it != std::sregex_iterator();
				++it)
			{
				std::string id = (*it)[2].str();
				std::string name = (*it)[1].str();

				int idValue = 0;
				auto [ptr, ec] = std::from_chars(
					id.data(),
					id.data() + id.size(),
					idValue
				);

				OpenView(name, idValue);
			}

			ImGui::LoadIniSettingsFromDisk("CurrentLayout.layout");
			layoutNameToopen.clear();
		}
	}








	void EditorLayout::SaveNewLayout(std::string_view layoutName)
	{
		rapidjson::Document doc;
		doc.SetObject();

		auto& alloc = doc.GetAllocator();

		doc.AddMember(
			"name",
			rapidjson::Value(layoutName.data(), alloc),
			alloc
		);

		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);

		std::ofstream file((PathManager::GetProjectPath() / "Editor/Layouts" / layoutNameToopen).generic_string() + ".layout");
		file << buffer.GetString();
	}
}