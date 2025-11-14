#include "Button.h"

#include "InputEngine/Input.h"

#include <sstream>

namespace Eclipse
{
    void Eclipse::Button::Update()
    {
        Math::Vector2i mousePosition = Utilities::MainSingleton::GetInstance<Input>().GetGameMousePos();

        std::stringstream stringStream;
        stringStream << "X: " << mousePosition.x << "   Y: " << mousePosition.y;

        LOG(stringStream.str());
    }
}
