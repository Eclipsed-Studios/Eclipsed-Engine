#include "WindowManager.h"

#include "ImGui/imgui.h"

#include "Timer.h"

#include "Debug/DebugInformationCollector.h"

#include "rapidjson/rapidjson/document.h"
#include "rapidjson/rapidjson/writer.h"
#include "rapidjson/rapidjson/stringbuffer.h"
#include "rapidjson/rapidjson/filewritestream.h"

namespace ENGINE_NAMESPACE::Editor
{
	void WindowManager::OpenWindow(const std::string& name, int aId)
	{
		if (name == "Console") OpenWindow<ConsoleWindow>(aId);
		if (name == "Hierarchy") OpenWindow<HierarchyWindow>(aId);
		if (name == "Inspector") OpenWindow<InspectorWindow>(aId);
	}
	void WindowManager::UpdateMainMenuBar()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Windows"))
			{
				if (ImGui::MenuItem("Console")) OpenWindow("Console", -1);
				if (ImGui::MenuItem("Hierarchy")) OpenWindow("Hierarchy", -1);
				if (ImGui::MenuItem("Inspector")) OpenWindow("Inspector", -1);

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Settings"))
			{
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
				std::string imguiWindowName = window->GetWindowName() + "##" + std::to_string(id);
				ImGui::Begin(imguiWindowName.c_str(), &window->myIsOpen, 0);
				window->Update();
				ImGui::End();

				++it;
			}
		}

		if (myShowDebugWindow)
		{
			DrawDebugInfoWindow();
		}
	}

	void WindowManager::Begin()
	{
		using namespace rapidjson;

		std::ifstream ifs(SETTINGS_PATH"editor.json");
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
				Value(pWindow->GetWindowName().c_str(), allocator).Move(),
				allocator
			);

			windowList.PushBack(window, allocator);
		}

		d.AddMember("OpenWindows", windowList, allocator);

		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		d.Accept(writer);

		std::ofstream ofs(SETTINGS_PATH"editor.json");
		ofs << buffer.GetString();
		ofs.close();
	}

	void WindowManager::DrawDebugInfoWindow()
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_pos = viewport->WorkPos;
		ImVec2 work_size = viewport->WorkSize;
		ImVec2 window_pos = ImVec2(work_pos.x + work_size.x, work_pos.y + work_size.y);
		ImVec2 window_pos_pivot = ImVec2(1.0f, 1.0f);

		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);

		ImGui::SetNextWindowBgAlpha(0.35f);

		ImGui::Begin("PerfTooltip", &myShowDebugWindow,
			ImGuiWindowFlags_NoDecoration |
			ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoFocusOnAppearing |
			ImGuiWindowFlags_NoNav);

		float fps = ImGui::GetIO().Framerate;
		float totalTime = Time::GetTotalTime();
		int renderCalls = DebugInformationCollector::GetRenderCalls();

		ImGui::Text("Render Calls: %d", renderCalls);
		ImGui::Text("FPS: %.1f", fps);
		ImGui::Text("Total Time: %.1f", totalTime);

		ImGui::End();
	}
}