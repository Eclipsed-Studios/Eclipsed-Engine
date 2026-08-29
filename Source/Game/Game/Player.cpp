#include "PlayerMovement.h"
#include "Player.h"

#include "EclipsedEngine/Components/Transform2D.h"

#include "EclipsedEngine/Components/Physics/RigidBody2D.h"

#include "EclipsedEngine/Components/Audio/AudioEmitter.h"

void Player::Start()
{
	CurrentCheckpointPosition = gameObject->transform->GetPosition();
}

void Player::Reset()
{
	Eclipse::RigidBody2D* rb = gameObject->GetComponent<Eclipse::RigidBody2D>();
	gameObject->transform->SetPosition(CurrentCheckpointPosition);

	rb->SetBodyPosition(CurrentCheckpointPosition);

	std::vector<Eclipse::GameObject*>& children = gameObject->GetChildren();
	for (auto& child : children)
	{
		if (child->GetName() == "DeathSoundObject")
		{
			child->GetComponent<Eclipse::AudioEmitter>()->Play();
		}
	}
}
