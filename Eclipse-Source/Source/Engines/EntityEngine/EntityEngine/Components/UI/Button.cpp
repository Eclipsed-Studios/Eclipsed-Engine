#include "Button.h"

#include "InputEngine/Input.h"

#include <sstream>

namespace Eclipse
{
    COMPONENT_REGISTRATION(Button);

    void Eclipse::Button::Update()
    {
        Math::Vector2i mousePosition = Input::GetGameMousePos();

        std::stringstream stringStream;
        stringStream << "X: " << mousePosition.x << "   Y: " << mousePosition.y;

        LOG(stringStream.str());
    }
}
