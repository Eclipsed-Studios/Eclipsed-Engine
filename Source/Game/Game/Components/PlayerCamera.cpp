#include "PlayerCamera.h"

#include "ECS/ComponentManager.h"
#include "Components/Transform2D.h"

namespace Eclipse
{
    void PlayerCamera::Awake()
    {
        myPlayerTransform = GetComp(Transform2D, myPlayerGO);
        myTransform = gameObject->GetComponent<Transform2D>();
    }

	void PlayerCamera::Update()
	{
        myTransform->SetPosition(myPlayerTransform->GetPosition() + Math::Vector2f(myPositionX, myPositionY));
	}
}