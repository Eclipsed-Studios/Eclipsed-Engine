#include "PlayerCamera.h"

#include "ECS/ComponentManager.h"
#include "Components/Transform2D.h"

namespace Eclipse
{
    void PlayerCamera::Awake()
    {
        myPlayerTransform = GetComp(Transform2D, myPlayerGO);
        myTransform = GetComp(Transform2D, gameObject);
    }

	void PlayerCamera::Update()
	{
        myTransform->SetPosition(myPlayerTransform->GetPosition() + Math::Vector2f(myPositionX, myPositionY));
	}
}