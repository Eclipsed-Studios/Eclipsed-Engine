#include "LayoutManager.h"

#include "CoreEngine/Files/FileUtilities.h"
#include "CoreEngine/Settings/EditorSettings.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filewritestream.h"
#include <fstream>

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"

bool Eclipse::Editor::LayoutManager::myOpenNameSelectPopup;
char Eclipse::Editor::LayoutManager::myNameSelectBuffer[128] = "";

std::vector<std::string> Eclipse::Editor::LayoutManager::myLayouts;

std::vector<Eclipse::Editor::LayoutWindowData> Eclipse::Editor::LayoutManager::OpenLayout(const std::string_view& layoutName)
{
	std::ifstream in(GetLayoutPath(std::string(layoutName)));

	if (!in.is_open()) return {};

	std::string jsonString((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());

	in.close();

	std::vector<LayoutWindowData> data;

	rapidjson::Document d;
	d.Parse(jsonString.c_str());

	if (d.HasParseError()) return {};

	if (d.HasMember("OpenWindows"))
	{
		for (const auto& v : d["OpenWindows"].GetArray())
		{
			int id = v["id"].GetInt();
			std::string name = v["name"].GetString();

			data.push_back({ id, name });
		}
	}

	return data;
}

void Eclipse::Editor::LayoutManager::ImportLayout()
{
	std::string filepath = Files::SelectFileDialog();

	std::ifstream in(filepath);

	if (!in.is_open()) return;

	std::string jsonString((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());

	in.close();

	std::string filename = std::filesystem::path(filepath).filename().stem().generic_string();

	std::ofstream out(GetLayoutPath(filename));

	out << jsonString;
	out.close();

	myLayouts.push_back(filename);
}

void Eclipse::Editor::LayoutManager::SaveLayout()
{
	SaveLayout("CurrentLayout");
}

void Eclipse::Editor::LayoutManager::SaveAsNewLayout()
{
	myOpenNameSelectPopup = true;
}

void Eclipse::Editor::LayoutManager::SaveLayout(const std::string& name)
{


	std::vector<Settings::OpenEditorWindows> openWindows = Settings::EditorSettings::GetCurrentlyOpenEditorWindows();

	rapidjson::Document d;
	d.SetObject();

	rapidjson::Value layoutList(rapidjson::kArrayType);
	for (const Settings::OpenEditorWindows& window : openWindows)
	{
		rapidjson::Value val(rapidjson::kObjectType);
		val.AddMember("id", window.ID, d.GetAllocator());
		val.AddMember("name", rapidjson::Value(window.Name.c_str(), d.GetAllocator()).Move(), d.GetAllocator());

		layoutList.PushBack(val, d.GetAllocator());
	}

	d.AddMember("OpenWindows", layoutList.Move(), d.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);

	std::string filename = std::filesystem::path(name).filename().stem().generic_string();


	std::ofstream out(GetLayoutPath(filename));

	out << buffer.GetString();
	out.close();
}

void Eclipse::Editor::LayoutManager::Update()
{
	if (myOpenNameSelectPopup)
		ImGui::OpenPopup("Save Layout As");

	if (ImGui::BeginPopupModal("Save Layout As", &myOpenNameSelectPopup, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Enter a new layout name:");
		ImGui::InputText("##layoutName", myNameSelectBuffer, IM_ARRAYSIZE(myNameSelectBuffer));

		ImGui::Spacing();

		if (ImGui::Button("Save", ImVec2(120, 0)))
		{
			if (strlen(myNameSelectBuffer) > 0)
			{
				SaveLayout(myNameSelectBuffer);
				myOpenNameSelectPopup = false;
				ImGui::CloseCurrentPopup();
			}
		}

		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0)))
		{
			myOpenNameSelectPopup = false;
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}


void Eclipse::Editor::LayoutManager::LoadLayouts()
{
	for (auto entry : std::filesystem::directory_iterator(PathManager::GetProjectRoot() / "Editor/Layouts/"))
	{
		std::string name = entry.path().filename().stem().string();

		if (name == "CurrentLayout") OpenLayout(name);
		else myLayouts.push_back(name);
	}
}

const std::vector<std::string>& Eclipse::Editor::LayoutManager::GetLayouts()
{
	return myLayouts;
}


std::filesystem::path Eclipse::Editor::LayoutManager::GetLayoutPath(const std::string& filename)
{
	return PathManager::GetProjectRoot() / "Editor/Layouts/" / (filename + ".edlayout");
}
