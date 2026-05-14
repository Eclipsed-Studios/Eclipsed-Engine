#pragma once

#include "AssetEngine/Core/GUID.h"

#include <unordered_map>
#include <typeindex>
#include <filesystem>
#include <fstream>

#include "Data/IAssetMeta.h"
#include "Data/AudioMeta.h"
#include "Data/TextureMeta.h"
#include "AssetEngine/Core/SupportedAssets.h"

#include "cereal/cereal.hpp"
#include <cereal/types/memory.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/string.hpp>

#include <memory>

namespace Eclipse::Assets
{
	struct AssetMeta
	{
		AssetMeta() = default;
		~AssetMeta();

		AssetMeta(const AssetMeta&) = delete;
		AssetMeta& operator=(const AssetMeta&) = delete;

		AssetMeta(AssetMeta&&) noexcept = default;
		AssetMeta& operator=(AssetMeta&&) noexcept = default;

		template<typename T, typename... Args>
		T* AddMetaComponent(Args... args);

		template<typename T>
		const T* GetMetaComponent() const;

		template<typename T>
		T* GetMetaComponent();

		template<typename T>
		bool HasMetaComponent()const;

		void WriteToStream(std::ofstream& _of) const;
		void LoadFromStream(std::ifstream& _if);

		void WriteToStreamBinary(std::ofstream& _of) const;
		void LoadFromStreamBinary(std::ifstream& _if);

		std::string GetArtifactPath() const;

		GUID guid;
		std::filesystem::path fullPath = "";
		std::filesystem::path exportedPath = "";
		AssetType type = AssetType::Unknown;

	private:
		std::unordered_map<std::string, std::unique_ptr<IAssetMeta>> metaComponents;

	public:
		template <class Archive>
		void serialize(Archive& ar, const std::uint32_t version);
	};



	template<typename T, typename ...Args>
	inline T* AssetMeta::AddMetaComponent(Args ...args)
	{
		auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
		T* raw = ptr.get();

		metaComponents[typeid(T).name()] = std::move(ptr);
		return raw;
	}

	template<typename T> 
	inline const T* AssetMeta::GetMetaComponent() const
	{
		if (!HasMetaComponent<T>()) return nullptr;

		return reinterpret_cast<const T*>(metaComponents.at(typeid(T).name()).get());
	}

	template<typename T>
	inline T* AssetMeta::GetMetaComponent()
	{
		if (!HasMetaComponent<T>()) return nullptr;

		return reinterpret_cast<T*>(metaComponents.at(typeid(T).name()).get());
	}

	template<typename T>
	inline bool AssetMeta::HasMetaComponent() const
	{
		return metaComponents.find(typeid(T).name()) != metaComponents.end();
	}

	template<class Archive>
	inline void AssetMeta::serialize(Archive& ar, const std::uint32_t version)
	{
		std::string guidStr = guid.ToString();

		ar(
			CEREAL_NVP(guidStr),
			CEREAL_NVP(type),
			CEREAL_NVP(metaComponents)
		);

		guid.FromString(guidStr);
	}
}