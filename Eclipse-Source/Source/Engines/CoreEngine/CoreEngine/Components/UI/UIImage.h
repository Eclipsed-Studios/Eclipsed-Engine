#pragma once

#include "CoreEngine/Components/Base/BaseComponent.h"

#include "CoreEngine/AssetManagement/Resources/Material.h"

namespace Eclipse
{
    class UIImage : public Component
    {
        BASE_SELECTION(UIImage, 0)

    public:
        void OnComponentAdded() override;
        void Render() override;
        void Draw();

        Material* myMaterial = nullptr;
    };
}