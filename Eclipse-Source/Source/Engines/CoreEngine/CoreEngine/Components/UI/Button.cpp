#include "Button.h"

#include "Input/Input.h"

#include <sstream>

void Eclipse::Button::Update()
{
    Math::Vector2i mousePosition = Input::GetGameMousePos();

    std::stringstream stringStream;
    stringStream << "X: " << mousePosition.x << "   Y: " << mousePosition.y;

    LOG(stringStream.str());
}
