#include "RectTransform.h"

namespace Eclipse
{
    void RectTransform::EarlyUpdate()
    {

    }

    void RectTransform::DrawInspector()
    {
        ImGui::Text("Position");
        ImGui::SameLine();
        ImGui::DragFloat2("##PositionRectTransform", (float*)Position.GetData());

        ImGui::Text("Size");
        ImGui::SameLine();
        ImGui::DragFloat2("##SizeRectTransform", (float*)WidthHeightPX.GetData());
    }
}