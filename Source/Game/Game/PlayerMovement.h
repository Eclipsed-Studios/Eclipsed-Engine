#pragma once

#include "EclipsedEngine/Components/Component.h"
#include "Core/Math/Vector/Vector2.h"

#include "Assets/Assets/AudioAsset.h"
#include "EclipsedEngine/Components/Audio/AudioEmitter.h"

namespace Eclipse
{
	class RigidBody2D;
}

class PlayerMovement : public Eclipse::Component
{
	COMPONENT_BASE_2(PlayerMovement, 0)

public:
	void Start() override;
	void Update() override;

	bool IsGrounded();
	void JumpLogic();

public:
	SERIALIZED_FIELD(float, MaxMovespeed);

private:
	Eclipse::RigidBody2D* rb = nullptr;
	Eclipse::AudioEmitter* AudioEmitter = nullptr;


	float Movespeed;
public:
	SERIALIZED_FIELD(float, Acceleration);

	SERIALIZED_FIELD(float, JumpForce);

	static inline Eclipse::Math::Vector2f Pos = {};

	SERIALIZED_FIELD(Eclipse::Math::Vector2f, GroundcheckOffset);


	SERIALIZED_FIELD(Eclipse::Assets::AudioClip, JumpSFX);
};