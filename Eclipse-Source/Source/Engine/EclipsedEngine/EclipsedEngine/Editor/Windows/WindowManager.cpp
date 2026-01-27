#include "WindowManager.h"

#include "ImGui/imgui.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filewritestream.h"
#include <fstream>

#include "EclipsedEngine/Editor/Windows/WindowTypes/Window.h"
#include "EclipsedEngine/Editor/ImGui/ImGui_Impl.h"

#include "CoreEngine/MainSingleton.h"
#include "CoreEngine/Settings/EngineSettings.h"

#include "EclipsedEngine/Replication/ReplicationManager.h"

#include "EclipsedEngine/Editor/Windows/WindowData.h"
//#include "CoreEngine/Settings/SettingsRegistry.h"

#include "CoreEngine/Settings/EditorSettings.h"

#include "CoreEngine/Debug/DebugLogger.h"

#include "CoreEngine/Files/FileUtilities.h"

#include "EclipsedEngine/Editor/Layout/LayoutManager.h"

namespace Eclipse::Editor
{
	void WindowManager::OpenWindow(const std::string& name, int aId)
	{
		AbstractWindow* window = static_cast<AbstractWindow*>(WindowRegistry::GetWindow(name));
		if (window == nullptr) return;


		AbstractWindow* newWindow = window->GetNewWindow(aId);

		if (aId == -1)
		{
			auto openWindows = Settings::EditorSettings::GetCurrentlyOpenEditorWindows();
			openWindows.push_back({ newWindow->instanceID, newWindow->windowName });
			Settings::EditorSettings::SetCurrentlyOpenEditorWindows(openWindows);
		}

		newWindow->Open();
		IdToWindow[newWindow->instanceID] = newWindow;

		WindowData data;
		data.id = newWindow->instanceID;
		data.name = newWindow->windowName;

		//Settings::SettingsRegistry::AddToList("editor.open-windows", data);
	}
	void WindowManager::UpdateMainMenuBar()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Select Project"))
				{
					//PathManager::SelectProject();
				}

				ImGui::EndMenu();
			}


			if (ImGui::BeginMenu("Windows"))
			{
				for (const auto& [name, window] : WindowRegistry::GetWindows())
				{
					if (!window->GetCategoryName())
					{
						if (ImGui::MenuItem(name.c_str())) OpenWindow(name.c_str(), -1);
					}
					else
					{
						std::string fullCategory = window->GetCategoryName();

						std::vector<std::string> categories = {};
						while (!fullCategory.empty())
						{
							size_t idx = fullCategory.find_first_of('/');
							std::string category = fullCategory.substr(0, idx);

							if (!category.empty())
								categories.push_back(category);

							if (idx == std::string::npos)
								break;

							fullCategory.erase(0, idx + 1);
						}

						AddWindowToCategory(categories, 0, name);
					}
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Settings"))
			{
				ImGui::EndMenu();
			}

		
			if (ImGui::MenuItem("Build"))
			{
				// AssetExporter::ExportAll();
				// std::string cmd = "cd \"" SOURCE "Tools"  "\" && build-game.bat";

				// int result = system(("start cmd /K \"" + cmd + "\"").c_str());

				// if (result != 0)
				// {
				// 	int i = 0;
				// }
			}

			if (ImGui::BeginMenu("Network"))
			{
				ImGui::Text("IP: ");
				ImGui::SameLine();

				char IP[17];
				memcpy(IP, Replication::ReplicationManager::IP.c_str(), Replication::ReplicationManager::IP.size() + 1);
				if (ImGui::InputText("##IpToUse", IP, 16))
				{
					std::ofstream stream("NetworkIp.ntwrk");
					stream << IP;
					stream.close();

					Replication::ReplicationManager::IP = IP;
				}

				ImGui::Checkbox("##Start Server Checkbox", &Replication::ReplicationManager::startServer);
				ImGui::SameLine();
				ImGui::Text("Start Server");

				ImGui::Checkbox("##Start Client Checkbox", &Replication::ReplicationManager::startClient);
				ImGui::SameLine();
				ImGui::Text("Start Client");

				ImGui::EndMenu();
			}

			const char* currentLayoutName = "Layout: Default";

			ImGui::SameLine(ImGui::GetWindowWidth() - (ImGui::CalcTextSize(currentLayoutName).x * 2) - 50);
			ImGui::SetNextItemWidth(ImGui::CalcTextSize(currentLayoutName).x * 2);

			static std::string currentItem = "Default";
			if (ImGui::BeginCombo("##Layouts", std::string("Layout: " + currentItem).c_str()))
			{
				/*if (ImGui::Button("Export"))
				{
					LayoutManager::Expo();
				}
				*/

				if (ImGui::Button("Import"))
				{
					LayoutManager::ImportLayout();
				}
				ImGui::SameLine();
				if (ImGui::Button("Save layout as"))
				{
					LayoutManager::SaveAsNewLayout();
				}

				ImGui::SeparatorText("Layouts");

				for (auto& layout : LayoutManager::GetLayouts())
				{
					bool isSelected = currentItem == layout;

					if (ImGui::Selectable(layout.c_str(), isSelected))
					{
						currentItem = layout;
						const auto& layoutWindows = LayoutManager::OpenLayout(layout.c_str());
						if (layoutWindows.empty()) break;

						for (auto& window : IdToWindow)
						{
							window.second->myIsOpen = false;
						}

						for (const auto& window : layoutWindows)
						{
							OpenWindow(window.name.c_str(), window.id);
						}
					}

					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}

			//if (ImGui::Button("Debug"))
			//{
			//	myShowDebugWindow = !myShowDebugWindow;
			//}

			ImGui::EndMainMenuBar();
		}
	}

	void WindowManager::Update()
	{
		UpdateMainMenuBar();

		LayoutManager::Update();

		for (auto it = IdToWindow.begin(); it != IdToWindow.end(); )
		{
			const int& id = it->first;
			AbstractWindow* window = it->second;

			if (window->myWasLastOpen != window->myIsOpen)
			{
				delete window;
				it = IdToWindow.erase(it);
			}
			else
			{
				std::string imguiWindowName = window->windowName + "##" + std::to_string(id);
				ImGui::PushID(id);
				ImGui::Begin(imguiWindowName.c_str(), &window->myIsOpen, window->flags);
				window->PreUpdate();
				window->Update();
				window->PostUpdate();
				ImGui::End();
				ImGui::PopID();

				if (!window->myIsOpen)
				{
					auto openWindows = Settings::EditorSettings::GetCurrentlyOpenEditorWindows();
					for (auto it = openWindows.begin(); it != openWindows.end();)
					{
						if (it->ID == window->instanceID) {
							openWindows.erase(it);
							Settings::EditorSettings::SetCurrentlyOpenEditorWindows(openWindows);
							Settings::EditorSettings::Save();
							break;
						}

						it++;
					}
					Settings::EditorSettings::SetCurrentlyOpenEditorWindows(openWindows);
				}

				++it;
			}
		}

		//if (myShowDebugWindow)
		//{
		//	myDebugWindow.PreUpdate();
		//	myDebugWindow.Update();
		//	myDebugWindow.PostUpdate();
		//}
	}

	void WindowManager::Begin()
	{
		LayoutManager::LoadLayouts();

		ImGui::LoadIniSettingsFromDisk("imgui.ini");
		using namespace rapidjson;

		//const std::vector<Settings::OpenEditorWindows>& openWindows = Settings::EditorSettings::GetCurrentlyOpenEditorWindows();

		//for (const Settings::OpenEditorWindows& openWindow : Settings::EditorSettings::GetCurrentlyOpenEditorWindows())
		//{
		//	OpenWindow(openWindow.Name.c_str(), openWindow.ID);
		//}
	}

	void WindowManager::End()
	{
		LayoutManager::SaveLayout();
		//using namespace rapidjson;

		//Document d;
		//d.SetObject();
		//Document::AllocatorType& allocator = d.GetAllocator();

		//Value windowList(kArrayType);
		//for (const auto& [id, pWindow] : IdToWindow)
		//{
		//	Value window(kObjectType);
		//	window.AddMember(
		//		"id",
		//		id,
		//		allocator
		//	);

		//	window.AddMember(
		//		"name",
		//		Value(pWindow->windowName.c_str(), allocator).Move(),
		//		allocator
		//	);

		//	windowList.PushBack(window, allocator);
		//}

		//d.AddMember("OpenWindows", windowList, allocator);

		//StringBuffer buffer;
		//Writer<StringBuffer> writer(buffer);
		//d.Accept(writer);

		//std::ofstream ofs(PathManager::GetConfigDir() / "editor.json");
		//ofs << buffer.GetString();
		//ofs.close();
	}

	void WindowManager::AddWindowToCategory(const std::vector<std::string>& categories, size_t idx, const std::string& windowName)
	{
		if (idx >= categories.size()) return;

		if (ImGui::BeginMenu(categories[idx].c_str()))
		{
			if (idx == categories.size() - 1)
			{
				if (ImGui::MenuItem(windowName.c_str()))
				{
					OpenWindow(windowName, -1);
				}
			}
			else
			{
				AddWindowToCategory(categories, idx + 1, windowName);
			}

			ImGui::EndMenu();
		}
	}
}