#include "ConsoleWindow.h"

#include <ImGui/imgui.h>
#include <DebugLogger.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <psapi.h>
#include <windows.h>
#include <iostream>

#include "ImGui/implot.h"

#include "Profiler/Profiler.h"

namespace Eclipse::Editor
{


	void DebugWindow::Open()
	{
		//flags = ImGuiWindowFlags_NoDecoration |
		//	//ImGuiWindowFlags_AlwaysAutoResize |
		//	ImGuiWindowFlags_NoSavedSettings |
		//	ImGuiWindowFlags_NoFocusOnAppearing |
		//	//ImGuiWindowFlags_NoNav |
		//	ImGuiWindowFlags_AlwaysVerticalScrollbar;

		MEMORYSTATUSEX memInfo;
		memInfo.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&memInfo);

		totalPhysMem = (int)(memInfo.ullTotalPhys / (1024 * 1024));
		totalVirtMem = (int)(memInfo.ullTotalVirtual / (1024 * 1024));

		for (int i = 0; i < Max_Entries; i++)
		{
			X[i] = i;
		}
	}

	void DebugWindow::PreUpdate()
	{
		//const ImGuiViewport* viewport = ImGui::GetMainViewport();
		//ImVec2 work_pos = viewport->WorkPos;
		//ImVec2 work_size = viewport->WorkSize;
		//ImVec2 window_pos = ImVec2(work_pos.x + work_size.x, work_pos.y + work_size.y);
		//ImVec2 window_pos_pivot = ImVec2(1.0f, 1.0f);

		//ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
		//ImGui::SetNextWindowBgAlpha(0.35f);

		//ImGui::Begin("DebugWindow", nullptr, flags);

		MEMORYSTATUSEX memInfo;
		memInfo.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&memInfo);
		PhysMemUsed = (int)((memInfo.ullTotalPhys - memInfo.ullAvailPhys) / (1024 * 1024));
	}

	void DebugWindow::Update()
	{
		if (!Profiler::ProfilerManager::IsStarted() && ImGui::Button("Start profiling"))
		{
			Profiler::ProfilerManager::BeginAndClearDataCollection();
		}

		if (Profiler::ProfilerManager::IsStarted() && ImGui::Button("Stop"))
		{
			Profiler::ProfilerManager::EndDataCollection();
		}



		//if (ImPlot::BeginPlot("MemoryUsage"))
		//{
		//	ImPlot::SetupAxis(ImAxis_X1, "Time (s)");
		//	ImPlot::SetupAxis(ImAxis_Y1, "Memory (MB)");

		//	ImPlot::SetNextLineStyle(ImVec4(1, 0, 0, 0.6f));
		//	ImPlot::PlotLine("CPU RAM", Time.data(), physicalMemoryCounter.data(), CurrentIndex, ImPlotLineFlags_None);

		//	ImPlot::SetNextLineStyle(ImVec4(0, 0, 1, 0.6f));
		//	ImPlot::PlotLine("GPU RAM", Time.data(), virtualMemoryCounter.data(), CurrentIndex, ImPlotLineFlags_None);


		//	for (auto& [name, data] : Profiler::ProfilerManager::GetRecords())
		//	{
		//		for (int i = 0; i < data.Count(); i++)
		//		{
		//			const Profiler::ProfileRecord& record = data.Get(i);

		//		}



		//	}


		//	ImPlot::EndPlot();
		//}








		float fps = ImGui::GetIO().Framerate;
		float totalTime = Time::GetTotalTime();
		int renderCalls = DebugInformationCollector::GetRenderCalls();

		//PROCESS_MEMORY_COUNTERS_EX pmc;
		//if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc)))
		//{
		//	PhysMemUsed = pmc.WorkingSetSize / (1024 * 1024);
		//	VirtuMemUsed = pmc.PrivateUsage / (1024 * 1024);

		//	physicalMemoryCounter[CurrentIndex] = PhysMemUsed;
		//	virtualMemoryCounter[CurrentIndex] = VirtuMemUsed;

		//	Time[CurrentIndex] = totalTime;

		//	CurrentIndex += 1;
		//	if (CurrentIndex >= Max_Entries) CurrentIndex = 0;
		//}



		//if (ImPlot::BeginPlot("MemoryUsage"))
		//{
		//	ImPlot::SetupAxis(ImAxis_X1, "Time (s)");
		//	ImPlot::SetupAxis(ImAxis_Y1, "Memory (MB)");

		//	ImPlot::SetNextLineStyle(ImVec4(1, 0, 0, 0.6f));
		//	ImPlot::PlotLine("CPU RAM", Time.data(), physicalMemoryCounter.data(), CurrentIndex, ImPlotLineFlags_None);

		//	ImPlot::SetNextLineStyle(ImVec4(0, 0, 1, 0.6f));
		//	ImPlot::PlotLine("GPU RAM", Time.data(), virtualMemoryCounter.data(), CurrentIndex, ImPlotLineFlags_None);

		//	ImPlot::EndPlot();
		//}

		//if (ImPlot::BeginPlot("Pie"))
		//{
		//	float values[] = { 30, 45, 25 };      // percentages or parts
		//	const char* labels[] = { "CPU", "GPU", "Other" };
		//	ImPlot::PlotPieChart(labels, values, 3, 0, 0, 10);

		//	ImPlot::EndPlot();
		//}

		//{
		//	const char* components[] = { "Physics", "AI", "Rendering", "Input" };
		//	float updateTimes[] = { 1.2f, 0.5f, 4.3f, 0.8f }; // ms per component

		//	if (ImPlot::BeginPlot("Component Update Times")) {
		//		ImPlot::SetupAxisTicks(ImAxis_X1, nullptr, 0, components); // label each bar
		//		ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 10); // set max expected ms
		//		ImPlot::PlotBars("Update Time", updateTimes, IM_ARRAYSIZE(updateTimes), 0.5f);
		//		ImPlot::EndPlot();
		//	}
		//}



		ImGui::Text("Ram: %d MB", totalPhysMem);
		ImGui::Text("Ram used: %d MB", PhysMemUsed);
		ImGui::Text("vRam used: %d MB", VirtuMemUsed);
		ImGui::Text("Render Calls: %d", renderCalls);
		ImGui::Text("FPS: %.1f", fps);
		ImGui::Text("Total Time: %.1f", totalTime);


		DISPLAY_DEVICE dd;
		dd.cb = sizeof(dd);

		int deviceIndex = 0;
		while (EnumDisplayDevices(0, deviceIndex, &dd, 0)) {
			DEVMODE dm;
			dm.dmSize = sizeof(dm);
			if (EnumDisplaySettings(dd.DeviceName, ENUM_CURRENT_SETTINGS, &dm)) {
				ImGui::Text(("Adapter: " + std::string(dd.DeviceString)).c_str());
				ImGui::Text(("Resolution: " + std::to_string(dm.dmPelsWidth) + " " + std::to_string(dm.dmPelsHeight)).c_str());
			}
			deviceIndex++;
		}
	}

	void DebugWindow::PostUpdate()
	{
		//ImGui::End();
	}
}
