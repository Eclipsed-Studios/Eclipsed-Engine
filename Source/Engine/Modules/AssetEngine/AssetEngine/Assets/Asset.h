#pragma once

#include <assert.h>

#include "AssetEngine/Core/GUID.h"

#include "CoreEngine/Settings/SettingsBase.hpp"

#include "cereal/cereal.hpp"
#include "cereal/types/string.hpp"

#define SET_TYPE(type) using Type = type;

#define SET_CONSTRUCTOR(cls) cls(AssetData* data) {dataPtr=reinterpret_cast<Type*>(data);} cls() = default;

#define ASSET_IMPL(cls, type)	\
SET_TYPE(type)					\
SET_CONSTRUCTOR(cls)



namespace Eclipse::Assets
{
	template<typename T>
	struct Asset {
		virtual ~Asset();
		virtual bool IsValid() const {
			return dataPtr != nullptr;
		}
		
		T* dataPtr = nullptr;

		GUID GetAssetID() const;
		GUID GetAssetID();

		static T* CreateNewData();


		template <class Archive> 
		void serialize(Archive& ar);
	};

	template<typename T>
	inline Asset<T>::~Asset()
	{
		if (IsValid())  return;

		
	}

	template<typename T>
	inline GUID Asset<T>::GetAssetID() const
	{
		return dataPtr->guid;
	}

	template<typename T>
	inline GUID Asset<T>::GetAssetID()
	{
		return dataPtr->guid;
	}

	template<typename T>
	inline T* Asset<T>::CreateNewData()
	{
		return new T;
	}

	template<typename T>
	template<class Archive>
	inline void Asset<T>::serialize(Archive& ar)
	{
		std::string assetGuid = GetAssetID().ToString();

		ar(
			cereal::make_nvp("guid", assetGuid)
		);

		GetAssetID().FromString(assetGuid);
	}
}