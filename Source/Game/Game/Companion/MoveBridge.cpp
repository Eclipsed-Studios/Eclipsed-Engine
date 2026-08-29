#include "MoveBridge.h"

#include "EclipsedEngine/Components/Transform2D.h"
#include "Core/Timer.h"

void MoveBridge::Interact()
{
	interacted = true;
}

void MoveBridge::Update()
{
    if (!interacted)
        return;

    float dt = Eclipse::Core::Timer::GetDeltaTime();

    if (!reachedTarget)
    {
        elapsed += dt;

        float t = std::clamp(elapsed / moveDuration, 0.0f, 1.0f);

        float x = std::lerp(startPos->x, targetPos->x, t);
        float y = std::lerp(startPos->y, targetPos->y, t);

        gameObject->transform->SetPosition({ x, y });

        if (t >= 1.0f)
        {
            reachedTarget = true;
            stayElapsed = 0.0f;
        }
    }
    else if (reachedTarget && !moveBack)
    {
        stayElapsed += dt;

        if (stayElapsed >= stayDuration)
        {
            //moveBack = true;
            elapsed = moveDuration;
        }
    }
    else if (reachedTarget && moveBack)
    {
        elapsed -= dt;

        float t = std::clamp(elapsed / moveDuration, 0.0f, 1.0f);

        float x = std::lerp(startPos->x, targetPos->x, t);
        float y = std::lerp(startPos->y, targetPos->y, t);

        gameObject->transform->SetPosition({ x, y });

        if (t <= 0.0f)
        {
            interacted = false;
            reachedTarget = false;
            moveBack = false;
            elapsed = 0.0f;
        }
    }
}