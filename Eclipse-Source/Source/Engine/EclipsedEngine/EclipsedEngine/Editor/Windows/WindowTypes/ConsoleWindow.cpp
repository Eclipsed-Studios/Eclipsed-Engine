#include "ConsoleWindow.h"

#include <ImGui/imgui.h>
#include "CoreEngine/Debug/DebugLogger.h"

namespace Eclipse::Editor
{
	void ConsoleWindow::Update()
	{
		//ImGui::Checkbox("Show Messages", &myShouldShowMessages);
		//ImGui::SameLine();
		//ImGui::Checkbox("Show Warnings", &myShouldShowWarnings);
		//ImGui::SameLine();
		//ImGui::Checkbox("Show Errors", &myShouldShowErrors);
		//ImGui::SameLine();
		//ImGui::Checkbox("Collapse", &myShouldCollapseMessages);
		//ImGui::SameLine();

		//if (myAlwaysAtBottom)
		//{
		//	ImGui::SetScrollY(ImGui::GetScrollMaxY());
		//}
		//

		//if (ImGui::Button("Clear"))DebugLogger::Clear();

		//ImGui::Separator();

		//for (const auto& message : DebugLogger::Get())
		//{
		//	if (message[0].type == DebugLogger::MessageTypes::Message && !myShouldShowMessages) continue;
		//	if (message[0].type == DebugLogger::MessageTypes::Warning && !myShouldShowWarnings) continue;
		//	if (message[0].type == DebugLogger::MessageTypes::Error && !myShouldShowErrors) continue;

		//	static ImVec4 amountColor = { 0.7f, 0.7f, 0.7f, 1.f };

		//	if (myShouldCollapseMessages)
		//	{
		//		const Message& message = messageList.back();

		//		DisplayMessage(message);

		//		ImGui::SameLine();
		//		ImGui::SetWindowFontScale(0.9f);
		//		ImGui::TextColored(amountColor, std::to_string(messageList.size()).c_str());
		//		ImGui::SetWindowFontScale(1.f);
		//		ImGui::Separator();
		//		continue;
		//	}

		//	for (const Message& message : messageList)
		//	{
		//		DisplayMessage(message);

		//		ImGui::Separator();
		//	}
		//}

		//if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY() - 100)
		//{
		//	myAlwaysAtBottom = true;
		//}
		//else
		//{
		//	myAlwaysAtBottom = false;
		//}
		//
	}
	void ConsoleWindow::DisplayMessage(const Message& aMessage)
	{
		/*ImVec4 color;
		switch (aMessage.type)
		{
		case MessageTypes::Message: color = { 1.f,1.f,1.f,1.f }; break;
		case MessageTypes::Warning: color = { 1.f,1.f,0.f,1.f }; break;
		case MessageTypes::Error:	color = { 1.f,0.f,0.f,1.f }; break;
		}

		static ImVec4 fileColor = { 0.7f, 0.7f, 0.7f, 1.f };
		static ImVec4 lineColor = { 0.88f, 0.88f, 0.2f, 1.f };
		static ImVec4 timeColor = { 0.5f, 0.5f, 0.5f, 1.f };

		ImGui::TextColored(color, aMessage.message.c_str());

		ImGui::Spacing();
		ImGui::SetWindowFontScale(0.9f);

		ImGui::TextColored(fileColor, aMessage.file.c_str());
		ImGui::TextColored(fileColor, "At line: ");
		ImGui::SameLine();
		ImGui::TextColored(lineColor, std::to_string(aMessage.line).c_str());
		ImGui::TextColored(timeColor, aMessage.timeString.c_str());
		ImGui::SetWindowFontScale(1.f);*/
	}
}
