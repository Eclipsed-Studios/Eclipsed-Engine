#ifdef ECLIPSED_EDITOR

#include "DragAndDrop.h"

namespace Eclipse::Editor
{
    inline bool DragAndDrop::BeginTarget(const char* text, const Utilities::FileInfo::FileType_& type)
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

    inline void DragAndDrop::BeginSource(const char* payload, const size_t& size, const Utilities::FileInfo& info)
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
        ImGui::PushTextWrapPos(ImGui::GetCursorPosX() + maxWidth - padding.x);

        ImVec2 textSize = ImGui::CalcTextSize(text, nullptr, false, maxWidth - padding.x * 2.0f);
        ImVec2 boxSize = ImVec2(maxWidth, textSize.y + padding.y * 2.0f);
        ImVec2 pos = ImGui::GetCursorScreenPos();

        ImGui::GetWindowDrawList()->AddRectFilled(
            pos, ImVec2(pos.x + boxSize.x, pos.y + boxSize.y),
            ImGui::GetColorU32({ aBgColor.r, aBgColor.g, aBgColor.b, 1.f }));

        ImGui::GetWindowDrawList()->AddRect(
            pos, ImVec2(pos.x + boxSize.x, pos.y + boxSize.y),
            ImGui::GetColorU32({ aBorderColor.r, aBorderColor.g, aBorderColor.b, 1.f }),
            0.0f, ImDrawFlags_RoundCornersNone, 1.5f);

        ImGui::SetCursorScreenPos(pos);
        bool clicked = ImGui::InvisibleButton("##hitbox", boxSize);

        ImGui::GetWindowDrawList()->AddText(
            ImVec2(pos.x + padding.x, pos.y + padding.y),
            ImGui::GetColorU32(ImGuiCol_Text), text);

        ImGui::SetCursorScreenPos(ImVec2(pos.x, pos.y + boxSize.y));

        ImGui::PopTextWrapPos();
        ImGui::PopID();

        return clicked;
    }
}

#endif