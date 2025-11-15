#include "Input.h"

#include "InputEngine/Input.h"

static Input l_input;

bool Input::GetKeyDown(Keycode keycode)
{
    return Eclipse::Input::GetKeyDown(keycode);
}

bool Input::GetKey(Keycode keycode)
{
    return Eclipse::Input::GetKey(keycode);
}

ECL_RUNTIME_API Input& GetInput()
{
    return l_input;
}
