#ifdef ECLIPSED_EDITOR

#include "DragAndDrop.h"

namespace Eclipse::Editor
{
    bool DragAndDrop::BeginTarget(const char* text, const Utilities::FileInfo::FileType_& type)
    {
        TextBox(text, { 5, 5 }, { 0,0,0,0 }, { 255, 255,255, 1 }, text);

        bool recievedData = false;
        if (ImGui::BeginDragDropTarget())
        {
            const char* dndString = dnd_id[type];

            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(dndString))
            {
                index = payload->DataSize;
                memcpy(payloadBuffer, payload->Data, payload->DataSize);

                recievedData = true;
            }
            ImGui::EndDragDropTarget();
        }

        return recievedData;
    }

    void DragAndDrop::BeginSource(const char* payload, const size_t& size, const Utilities::FileInfo& info)
    {
        if (DragAndDrop::dnd_id.find(info.type) != DragAndDrop::dnd_id.end())
        {
            if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
            {
                std::memset(payloadBuffer, 0, sizeof(payloadBuffer));

                memcpy(&payloadBuffer[0], payload, size);
                const char* dnd = DragAndDrop::dnd_id[info.type];

                index = size;
                ImGui::SetDragDropPayload(dnd, payloadBuffer, size + 1);

                ImGui::Text(payload);
                ImGui::EndDragDropSource();
            }
        }
    }

    bool DragAndDrop::TextBox(const char* text, Math::Vector2f padding, const Math::Color& aBgColor, const Math::Color& aBorderColor, const char* id)
    {
        ImGui::PushID(id);

        float availableWidth = ImGui::GetContentRegionAvail().x;
        float maxWidth = availableWidth > 50.0f ? availableWidth : 50.0f;

        // Fixed height for your box
        const float boxHeight = ImGui::GetTextLineHeightWithSpacing() + padding.y * 2.0f;

        // Calculate box size
        ImVec2 boxSize(maxWidth, boxHeight);
        ImVec2 pos = ImGui::GetCursorScreenPos();

        // Draw background
        ImGui::GetWindowDrawList()->AddRectFilled(
            pos, ImVec2(pos.x + boxSize.x, pos.y + boxSize.y),
            ImGui::GetColorU32({ aBgColor.r, aBgColor.g, aBgColor.b, 1.f }));

        // Draw border
        ImGui::GetWindowDrawList()->AddRect(
            pos, ImVec2(pos.x + boxSize.x, pos.y + boxSize.y),
            ImGui::GetColorU32({ aBorderColor.r, aBorderColor.g, aBorderColor.b, 1.f }),
            0.0f, ImDrawFlags_RoundCornersNone, 1.5f);

        // Hit box
        ImGui::SetCursorScreenPos(pos);
        bool clicked = ImGui::InvisibleButton("##hitbox", boxSize);

        // Clip text so it doesn’t overflow the box
        ImVec2 textPos(pos.x + padding.x, pos.y + padding.y);
        ImVec2 clipMax(pos.x + boxSize.x - padding.x, pos.y + boxSize.y - padding.y);

        ImGui::GetWindowDrawList()->PushClipRect(textPos, clipMax, true);
        ImGui::GetWindowDrawList()->AddText(
            textPos,
            ImGui::GetColorU32(ImGuiCol_Text),
            text);
        ImGui::GetWindowDrawList()->PopClipRect();

        // Advance cursor below box
        ImGui::SetCursorScreenPos(ImVec2(pos.x, pos.y + boxSize.y));

        ImGui::PopID();

        return clicked;

    }
}

#endif