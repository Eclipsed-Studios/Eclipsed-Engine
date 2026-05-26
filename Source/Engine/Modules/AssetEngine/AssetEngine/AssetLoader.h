#pragma once

#include "Core/GUID.h"
#include "AssetTypes/IAssetType.h"

#include "AssetCache.h"

#include "CoreEngine/MainSingleton.h"
#include "AssetTypeRegistry.h"

#include "Core/EditorAssetDatabase.h"

namespace Eclipse::Assets
{
	class AssetLoader
	{
	public:
		template<typename T>
		static AssetData* Load(const GUID& guid);

		template<typename T>
		static AssetData* LoadDefaultAsset(DefaultAssetType assetType);
	};


	template<typename T>
	inline AssetData* AssetLoader::Load(const GUID& guid)
	{
		AssetData* data = AssetCache::Get(guid);
		if (data == nullptr)
		{
#ifdef ECLIPSED_EDITOR
			BinaryReader reader(guid);
#else
			BinaryReader reader("packed_file.bundle");
			//BinaryReader reader("C:/MyFiles/Projects/Project-Nova/Build/packed_file.bundle");
#endif

			const AssetMeta& meta = MainSingleton::GetInstance<AssetDatabase>().GetProcessedFile(guid);

			data = AssetCache::Store(guid, T::CreateNewData());
			IAssetType* type = AssetTypeRegistry::GetType(meta.type);

#ifdef ECLIPSED_EDITOR
			type->Load(reader, meta, data);
#else
			type->LoadFromBinary(reader, meta, data);
#endif
		}
//#ifdef ECLIPSED_EDITOR
//		else
//		{
//			BinaryReader reader(guid);
//			const AssetMeta& meta = MainSingleton::GetInstance<AssetDatabase>().GetProcessedFile(guid);
//			IAssetType* type = AssetTypeRegistry::GetType(meta.type);
//			type->Load(reader, meta, data);
//		}
//#endif

		return data;
	}

	template<typename T>
	inline AssetData* AssetLoader::LoadDefaultAsset(DefaultAssetType assetType)
	{
		IAssetType* type = AssetTypeRegistry::GetType<T>();
		GUID guid = type->GetDefaultAsset(assetType);

		AssetData* data = AssetCache::Get(guid);
		if (data == nullptr)
		{
#ifdef ECLIPSED_EDITOR
			BinaryReader reader(guid);
#else
			BinaryReader reader("packed_file.bundle");
			//BinaryReader reader("C:/MyFiles/Projects/Project-Nova/Build/packed_file.bundle");
#endif

			const AssetMeta& meta = MainSingleton::GetInstance<AssetDatabase>().GetProcessedFile(guid);

			data = AssetCache::Store(guid, T::CreateNewData());

#ifdef ECLIPSED_EDITOR
			type->Load(reader, meta, data);
#else
			type->LoadFromBinary(reader, meta, data);
#endif
		}

		return data;
	}
}