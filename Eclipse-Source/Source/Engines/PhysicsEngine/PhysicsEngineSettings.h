#pragma once

#include <vector>
#include "Math/Vector/Vector2.h"

#include <string>

#include "defines.h"

#include "Reflection/SerializedEnum.hpp"
#include <string>
#include <unordered_map>
#define MAX_LAYERS 16


namespace Eclipse
{
	static inline uint64_t myCollisionLayers[MAX_LAYERS] = {};

	constexpr int layerCount = 8;
#define LAYER_ENUM_ITEMS(X)                \
    X(Default, 1 << 0)                     \
    X(Player, 1 << 1)                      \
    X(Enemy, 1 << 2)                       \
    X(Projectile, 1 << 3)                  \
    X(Ground, 1 << 4)                      \
    X(Trigger, 1 << 5)                     \
    X(IgnoreRaycast, 1 << 6)               \
    X(UI, 1 << 7)                          \
    X(All, (1 << (layerCount)) - 1)

	SERIALIZABLE_ENUM(Layer, LAYER_ENUM_ITEMS);
#undef LAYER_ENUM_ITEMS


	enum DebugDrawTypes
	{
		drawShapes,
		drawJoints,
		drawJointExtras,
		drawBounds,
		drawMass,
		drawBodyNames,
		drawContacts,
		drawGraphColors,
		drawContactNormals,
		drawContactImpulses,
		drawContactFeatures,
		drawFrictionImpulses,
		drawIslands,

		drawQueries,
	};

	enum Box2DBodyType
	{
		StaticBody = 0,
		KinematicBody = 1,
		DynamicBody = 2
	};

	struct RigidBodySettings
	{
		Box2DBodyType BodyType = StaticBody;

		bool LockRotation = false;
		bool LockXPos = false;
		bool LockYPos = false;
	};

	struct UserData
	{
		unsigned gameobject = 0;
	};

	struct HitResult
	{
		Math::Vector2f point;
		Math::Vector2f normal;
		float fraction;
		unsigned gameobject;
	};

	struct HitResults
	{
		std::vector<HitResult> results;
	};

	struct Ray
	{
		Math::Vector2f position;
		Math::Vector2f direction;
	};
}
