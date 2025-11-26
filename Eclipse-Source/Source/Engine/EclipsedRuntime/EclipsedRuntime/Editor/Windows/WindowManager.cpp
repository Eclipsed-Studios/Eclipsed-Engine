#include "WindowManager.h"

#include "ImGui/imgui.h"

#include "rapidjson/rapidjson/document.h"
#include "rapidjson/rapidjson/writer.h"
#include "rapidjson/rapidjson/stringbuffer.h"
#include "rapidjson/rapidjson/filewritestream.h"
#include <fstream>

#include "EclipsedRuntime/Editor/Windows/WindowTypes/Window.h"

#include "EclipsedRuntime/Editor/ImGui/ImGui_Impl.h"

#include "NetworkEngine/Replication/ReplicationManager.h"

namespace Eclipse::Editor
{
	WindowManager::WindowManager()
	{
		//myDebugWindow.Open();
	}

	void WindowManager::LoadLayouts()
	{
		for (auto entry : std::filesystem::directory_iterator(PathManager::GetEngineAssets() / "Editor/Layouts/"))
		{


			myLayouts.push_back(entry.path().filename().string());
		}
	}

	void WindowManager::OpenWindow(const std::string& name, int aId)
	{
		AbstractWindow* window = static_cast<AbstractWindow*>(WindowRegistry::GetWindow(name));
		if (window == nullptr) return;

		AbstractWindow* newWindow = window->GetNewWindow(aId);

		newWindow->Open();
		IdToWindow[newWindow->instanceID] = newWindow;
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

			if (ImGui::BeginMenu("Layouts"))
			{
				if (ImGui::BeginMenu("Saved Layouts"))
				{
					if (ImGui::MenuItem("Default"))
					{
						OpenLayout("Default");
						return;
					}
					if (ImGui::MenuItem("Testing"))
					{
						OpenLayout("Testing");
						return;
					}
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Saving"))
				{
					if (ImGui::MenuItem("Default"))
					{
						ImGui::SaveIniSettingsToDisk((PathManager::GetEngineAssets() / "Editor/Layouts/Default.ini").generic_string().c_str());
					}
					if (ImGui::MenuItem("Testing"))
					{
						ImGui::SaveIniSettingsToDisk((PathManager::GetEngineAssets() / "Editor/Layouts/Testing.ini").generic_string().c_str());
					}

					ImGui::EndMenu();
				}

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
				ImGui::Checkbox("##Start Server Checkbox", &Replication::ReplicationManager::startServer);
				ImGui::SameLine();
				ImGui::Text("Start Server");

				ImGui::Checkbox("##Start Client Checkbox", &Replication::ReplicationManager::startClient);
				ImGui::SameLine();
				ImGui::Text("Start Client");

				ImGui::EndMenu();
			}

			ImGui::SameLine(ImGui::GetWindowWidth() - (ImGui::CalcTextSize("Debug").x * 2) + 10);
			if (ImGui::Button("Debug"))
			{
				myShowDebugWindow = !myShowDebugWindow;
			}

			ImGui::EndMainMenuBar();
		}
	}

	void WindowManager::Update()
	{
		UpdateMainMenuBar();

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
				ImGui::Begin(imguiWindowName.c_str(), &window->myIsOpen, window->flags);
				window->PreUpdate();
				window->Update();
				window->PostUpdate();
				ImGui::End();

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
		LoadLayouts();

		using namespace rapidjson;

		std::ifstream ifs(PathManager::GetEngineLocal() / "editor.json");
		if (!ifs.is_open()) {

		}

		std::string jsonString((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>());

		ifs.close();

		Document d;
		d.Parse(jsonString.c_str());

		if (d.HasMember("OpenWindows"))
		{
			const Value& windowList = d["OpenWindows"];
			for (auto& window : windowList.GetArray())
			{
				const Value& vID = window["id"];
				const Value& vName = window["name"];

				const int id = vID.GetInt();
				const std::string name = vName.GetString();

				OpenWindow(name, id);
			}
		}
	}

	void WindowManager::End()
	{
		using namespace rapidjson;

		Document d;
		d.SetObject();
		Document::AllocatorType& allocator = d.GetAllocator();

		Value windowList(kArrayType);
		for (const auto& [id, pWindow] : IdToWindow)
		{
			Value window(kObjectType);
			window.AddMember(
				"id",
				id,
				allocator
			);

			window.AddMember(
				"name",
				Value(pWindow->windowName.c_str(), allocator).Move(),
				allocator
			);

			windowList.PushBack(window, allocator);
		}

		d.AddMember("OpenWindows", windowList, allocator);

		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		d.Accept(writer);

		std::ofstream ofs(PathManager::GetConfigDir() / "editor.json");
		ofs << buffer.GetString();
		ofs.close();
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

	void WindowManager::OpenLayout(const char* aName)
	{
		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();

		ImGui_Impl::currentEditorLayout = aName;

		ImGui_Impl::ImplementImGui(Utilities::MainSingleton::GetInstance<GLFWwindow*>());
		ImGui_Impl::NewFrame();
	}
}