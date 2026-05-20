#pragma once

#include <assert.h>

#include "AssetEngine/Core/GUID.h"

#include "CoreEngine/Settings/SettingsBase.hpp"

#include "cereal/cereal.hpp"
#include "cereal/types/string.hpp"

#include "AssetEngine/AssetDeletionQueue.h"

#define SET_TYPE(type) using Type = type;

#define SET_CONSTRUCTOR(cls) cls(AssetData* data) { dataPtr=reinterpret_cast<Type*>(data);dataPtr->IncreaseRefCount();} cls() = default;

#define ASSET_IMPL(cls, type)	\
SET_TYPE(type)					\
SET_CONSTRUCTOR(cls)



namespace Eclipse::Assets
{
	template<typename T>
	struct Asset
	{
		virtual ~Asset();

		Asset() = default;

		Asset(T* data)
			: dataPtr(data)
		{
			if (dataPtr)
				dataPtr->IncreaseRefCount();
		}

		// Copy constructor
		Asset(const Asset& other)
			: dataPtr(other.dataPtr)
		{
			if (dataPtr)
				dataPtr->IncreaseRefCount();
		}

		// Move constructor
		Asset(Asset&& other) noexcept
			: dataPtr(other.dataPtr)
		{
			other.dataPtr = nullptr;
		}

		// Copy assignment
		Asset& operator=(const Asset& other)
		{
			if (this == &other)
				return *this;

			if (dataPtr)
				dataPtr->DecreaseRefCount();

			dataPtr = other.dataPtr;

			if (dataPtr)
				dataPtr->IncreaseRefCount();

			return *this;
		}

		// Move assignment
		Asset& operator=(Asset&& other) noexcept
		{
			if (this == &other)
				return *this;

			if (dataPtr)
				dataPtr->DecreaseRefCount();

			dataPtr = other.dataPtr;
			other.dataPtr = nullptr;

			return *this;
		}

		T* dataPtr = nullptr;

		bool IsValid() const;
		GUID GetAssetID() const;
		GUID GetAssetID();

		static T* CreateNewData();

		template<class Archive>
		void serialize(Archive& ar);
	};


	template<typename T>
	inline Asset<T>::~Asset()
	{
		if (!IsValid())  return;

		dataPtr->DecreaseRefCount();
	}

	template<typename T>
	inline bool Asset<T>::IsValid() const
	{
		return dataPtr != nullptr;
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