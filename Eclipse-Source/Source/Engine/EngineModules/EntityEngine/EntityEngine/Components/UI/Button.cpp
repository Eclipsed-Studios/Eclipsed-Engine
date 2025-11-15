#include "Button.h"

#include "InputEngine/Input.h"

#include <sstream>

namespace Eclipse
{
    void Button::Update()
    {


        Input::GetMouseUp(Keycode::Scancode::MOUSE_LEFT);
        //Math::Vector2i mousePosition = ;

        //std::stringstream stringStream;
        //stringStream << "X: " << mousePosition.x << "   Y: " << mousePosition.y;

        //LOG(stringStream.str());
    }
}
