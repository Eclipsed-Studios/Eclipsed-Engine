#include "ChangeColor.h"

#include "EclipsedEngine/Components/Transform2D.h"
#include "Core/Timer.h"

#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"

void ChangeColor::Interact()
{
    gameObject->GetComponent<Eclipse::SpriteRenderer2D>()->SetColor(NewColor);
}