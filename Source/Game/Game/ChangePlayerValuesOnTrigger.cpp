#include "ChangePlayerValuesOnTrigger.h"
#include <EclipsedEngine/DebugLogger.h>

#include "PlayerMovement.h"

void ChangePlayerValuesOnTrigger::OnTriggerEnter(Eclipse::GameObject* OtherObject)
{
	PlayerMovement* PlayerMove = OtherObject->GetComponent<PlayerMovement>();
	if (!PlayerMove)
		return;

	if (ChangeSpeed)
	{
		OriginalMaxSpeed = PlayerMove->MaxMovespeed;

		PlayerMove->MaxMovespeed *= 3;
	}
	else if (ChangeJumpheight)
	{
		OriginalJumpHeight = PlayerMove->JumpForce;

		PlayerMove->JumpForce *= 6;
	}

}

void ChangePlayerValuesOnTrigger::OnTriggerExit(Eclipse::GameObject* OtherObject)
{
	PlayerMovement* PlayerMove = OtherObject->GetComponent<PlayerMovement>();
	if (!PlayerMove)
		return;

	if (ChangeSpeed)
	{
		PlayerMove->MaxMovespeed = OriginalMaxSpeed;
	}
	else if (ChangeJumpheight)
	{
		PlayerMove->JumpForce = OriginalJumpHeight;
	}
}