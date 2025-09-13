#include "Button.h"

#include "ImGui/ImGui/imgui.h"

#include <sstream>

void Eclipse::UIButton::Update()
{
}

void Eclipse::UIButton::DrawInspector()
{
    std::stringstream ss;
    ss << "##" << this;

    float d[2];

    ImGui::Text("Min");
    ImGui::SameLine();
    ImGui::DragFloat2(("##MIN" + ss.str()).c_str(), &d[0]);

    ImGui::Text("Max");
    ImGui::SameLine();
    ImGui::DragFloat2(("##MAX" + ss.str()).c_str(), &d[0]);
}
