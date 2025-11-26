#include "ReplicationWindow.h"

#include "ImGui/imgui.h"

#include "NetworkEngine/Replication/ReplicationManager.h"

namespace Eclipse::Editor
{
    void ReplicationWindow::Update()
    {
        static bool collisionLayersShown = false;
        collisionLayersShown = ImGui::CollapsingHeader("Collision Layers");

        static bool sceneShown = false;
        sceneShown = ImGui::CollapsingHeader("Scene Build Settings");

        if (sceneShown) DrawSceneEditor();
    }

    void ReplicationWindow::DrawSceneEditor()
    {
        if (ImGui::Button("Listen Server"))
        {
            
        }
    }
}