#include "Button.h"

#include "Input/Input.h"

#include <sstream>

namespace Eclipse
{
    COMPONENT_REGISTRATION(UIButton);

    void UIButton::Update()
    {
    }
    
    void Eclipse::Button::Update()
    {
        Math::Vector2i mousePosition = Input::GetGameMousePos();

        std::stringstream stringStream;
        stringStream << "X: " << mousePosition.x << "   Y: " << mousePosition.y;

        LOG(stringStream.str());
    }
}
