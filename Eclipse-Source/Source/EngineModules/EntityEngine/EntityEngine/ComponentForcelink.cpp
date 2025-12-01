#include "ComponentForcelink.h"

#include "EntityEngine/Components/AudioSource.h"
#include "EntityEngine/Components/Transform2D.h"
#include "EntityEngine/Components/Physics/BoxCollider2D.h"
#include "EntityEngine/Components/Physics/CapsuleCollider2D.h"
#include "EntityEngine/Components/Physics/CircleCollider2D.h"
#include "EntityEngine/Components/Physics/PolygonCollider2D.h"
#include "EntityEngine/Components/Physics/RigidBody2D.h"

#include "EntityEngine/Components/Rendering/Camera.h"
#include "EntityEngine/Components/Rendering/SpriteRenderer2D.h"
#include "EntityEngine/Components/Rendering/SpriteSheetAnimator.h"
#include "EntityEngine/Components/Rendering/TextRenderer.h"

#include "EntityEngine/Components/UI/Button.h"
#include "EntityEngine/Components/UI/Canvas.h"
#include "EntityEngine/Components/UI/RectTransform.h"
#include "EntityEngine/Components/UI/UIImage.h"

void Eclipse::ComponentForcelink::LinkComponents()
{
	COMP_REG(Transform2D);
	COMP_REG(BoxCollider2D);
	COMP_REG(CapsuleCollider2D);
	COMP_REG(CircleCollider2D);
	COMP_REG(PolygonCollider2D);
	COMP_REG(RigidBody2D);

	COMP_REG(Camera);
	COMP_REG(SpriteRenderer2D);
	COMP_REG(TextRenderer);

	COMP_REG(Button);
	COMP_REG(Canvas);
	COMP_REG(RectTransform);
	COMP_REG(UIImage);
}
