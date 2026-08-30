#include "ChangeSprite.h"

#include "EclipsedEngine/Components/Transform2D.h"
#include "Core/Timer.h"

#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"

void ChangeSprite::Interact()
{
    gameObject->GetComponent<Eclipse::SpriteRenderer2D>()->SetSprite(NewSprite);
}