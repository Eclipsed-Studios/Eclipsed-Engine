#include "ConsoleWindow.h"

#include <ImGui/imgui.h>
#include <DebugLogger.h>

namespace Eclipse::Editor
{
	void ConsoleWindow::Update()
	{
		ImGui::Checkbox("Show Messages", &myShouldShowMessages);
		ImGui::SameLine();
		ImGui::Checkbox("Show Warnings", &myShouldShowWarnings);
		ImGui::SameLine();
		ImGui::Checkbox("Show Errors", &myShouldShowErrors);
		ImGui::SameLine();
		ImGui::Checkbox("Collapse", &myShouldCollapseMessages);
		ImGui::SameLine();
		if (ImGui::Button("Clear"))DebugLogger::Clear();

		ImGui::Separator();

		for (const auto& [messageString, messageList] : DebugLogger::GetMessaes())
		{
			if (messageList[0].type == MessageTypes::Message && !myShouldShowMessages) continue;
			if (messageList[0].type == MessageTypes::Warning && !myShouldShowWarnings) continue;
			if (messageList[0].type == MessageTypes::Error && !myShouldShowErrors) continue;

			ImVec4 color;
			switch (messageList[0].type)
			{
			case MessageTypes::Message: color = { 1.f,1.f,1.f,1.f }; break;
			case MessageTypes::Warning: color = { 1.f,1.f,0.f,1.f }; break;
			case MessageTypes::Error:	color = { 1.f,0.f,0.f,1.f }; break;
			}

			if (myShouldCollapseMessages)
			{
				const Message& message = messageList.back();

				ImGui::TextColored(color, messageString.c_str());
				static ImVec4 timeColor = { 0.5f, 0.5f, 0.5f, 1.f };
				static ImVec4 amountColor = { 0.7f, 0.7f, 0.7f, 1.f };

				ImGui::TextColored(timeColor, (message.timeString + "\t\t\t").c_str());
				ImGui::SameLine();
				ImGui::TextColored(amountColor, std::to_string(messageList.size()).c_str());
				ImGui::Separator();
				continue;
			}

			for (const Message& message : messageList)
			{
				ImGui::TextColored(color, messageString.c_str());
				static ImVec4 timeColor = { 0.5f, 0.5f, 0.5f, 1.f };

				ImGui::TextColored(timeColor, message.timeString.c_str());
				ImGui::Separator();
			}
		}
	}
}
