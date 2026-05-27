#pragma once

#include "AssetEngine/Assets/PrefabAsset.h"

#include "EclipsedEngine/Components/Component.h"

#include "EclipsedEngine/ECS/ObjectManager.h"
#include "Input/Input.h"

namespace Eclipse
{
	class PlayerSpawner : public Component
	{
		BASE_SELECTION(PlayerSpawner, 10);

	public:
		void StartGame()
		{
			//if (Replication::ReplicationManager::ClickedHostButton)
			//{
			//	Instantiate(soulForgePrefab, gameObject, true);
			//}
			//else
			//{

			//	Instantiate(soulSuckerPrefab, gameObject, true);
			//}

			Instantiate(soulForgePrefab, gameObject, true);
		}

	public:

		SERIALIZED_FIELD(Assets::Prefab, soulForgePrefab);
		SERIALIZED_FIELD(Assets::Prefab, soulSuckerPrefab);

	};
}
