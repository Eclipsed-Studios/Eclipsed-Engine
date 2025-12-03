#pragma once

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

#include <vector>

namespace Eclipse
{
    class GameObject;

    namespace Editor
    {
        class EditorActions
        {
        public:
            enum Action
            {
                A_NONE,

                A_Save,

                A_Copy,
                A_Paste,
                A_Duplicate,

                A_Undo,
                A_Redo
            };

        public:
            EditorActions() = default;
            ~EditorActions() = default;

            static void Update();

            static void SaveScene();
            static void Save();

            static void CopyGameObject(unsigned activeGO, rapidjson::Value& gameobjectJson, rapidjson::Document::AllocatorType& anAllocator);
            static void CopyObject();
            static void Copy();

            static void StartChildren(std::vector<GameObject*>& aChildComponents);
            static void PasteGameObject(GameObject*& aGameObject, rapidjson::Value& gameobject, rapidjson::Document::AllocatorType& anAllocator);
            static void PasteObject();
            static void Paste();

            static void ReactToAction(Action anAction);

        };
    }
}