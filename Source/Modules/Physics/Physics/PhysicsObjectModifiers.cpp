#include "PhysicsEngine.h"

#include "box2d/box2d.h"
#include <bit>

namespace Eclipse
{
	void PhysicsEngine::ChangeBodyType(b2BodyId* aBodyID, BodyType aBodyType)
	{
		if (!aBodyID) return;
		b2Body_SetType(*aBodyID, static_cast<b2BodyType>(aBodyType));
	}

	void PhysicsEngine::SetPhysicsMaterial(b2ShapeId* aShape, const PhysMaterial& material)
	{
		b2SurfaceMaterial b2SurfaceMaterial = {};

		b2SurfaceMaterial.friction = material.friction;
		b2SurfaceMaterial.restitution = material.restitusion;

		b2Shape_SetSurfaceMaterial(*aShape, &b2SurfaceMaterial);
	}

	void PhysicsEngine::ChangeLayer(b2ShapeId* aShapeID, Layer aLayer)
	{
		b2Filter filter;
		filter.categoryBits = static_cast<uint64_t>(aLayer);

		int layerIndex = std::countr_zero(static_cast<uint32_t>(aLayer));
		filter.maskBits = myCollisionLayers[layerIndex];

		b2Shape_SetFilter(*aShapeID, filter);
	}

	void PhysicsEngine::ChangeRBLocks(b2BodyId* aBodyID, bool XLock, bool YLock, bool RotationLock)
	{
		auto ml = b2MotionLocks(XLock, YLock, RotationLock);

		b2Body_SetMotionLocks(*aBodyID, ml);
		b2Body_SetAwake(*aBodyID, true);
	}


	void PhysicsEngine::SetTransform(b2BodyId* aBodyID, const Math::Vector2f& aPosition, float aRotation)
	{
		b2Rot rot;
		rot.c = cosf(aRotation);
		rot.s = sinf(aRotation);

		b2Body_SetTransform(*aBodyID, b2Vec2(aPosition.x, aPosition.y), rot);
	}

	void PhysicsEngine::SetTransformBox(b2ShapeId* aShapeID, const Math::Vector2f& aScale, const Math::Vector2f& aPivot)
	{
		b2Polygon polygon = b2MakeOffsetBox(aScale.x, aScale.y, { aPivot.x, aPivot.y }, { 1, 0 });
		b2Shape_SetPolygon(*aShapeID, &polygon);
	}

	void PhysicsEngine::SetTransformCircle(b2ShapeId* aShapeID, float aRadius, const Math::Vector2f& aPivot)
	{
		b2Circle circle({ aPivot.x, aPivot.y }, aRadius);
		b2Shape_SetCircle(*aShapeID, &circle);
	}

	void PhysicsEngine::SetTransformCapsule(b2ShapeId* aShapeID, float aRadius, float aHalfHeight, const Math::Vector2f& aPivot)
	{
		b2Capsule capsule({ aPivot.x, -aHalfHeight * 0.5f + aPivot.y }, { aPivot.x, aHalfHeight * 0.5f + aPivot.y }, aRadius);
		b2Shape_SetCapsule(*aShapeID, &capsule);
	}

	void PhysicsEngine::SetTransformPolygon(b2ShapeId* aShapeID, const std::vector<Math::Vector2f>& aPoints, const Math::Vector2f& aScale, const Math::Vector2f& aPivot)
	{
		int pointCount = std::min(static_cast<int>(aPoints.size()), 8);

		std::vector<b2Vec2> vecOfVec;
		for (auto& vec : aPoints)
			vecOfVec.emplace_back(b2Vec2{ vec.x * aScale.x * 10.f, vec.y * aScale.y * 10.f });

		b2Hull hull = b2ComputeHull(vecOfVec.data(), pointCount);

		if (!b2ValidateHull(&hull))
			return;

		b2Polygon polygon = b2MakePolygon(&hull, 0.0001f);

		b2Shape_SetPolygon(*aShapeID, &polygon);
	}
}
