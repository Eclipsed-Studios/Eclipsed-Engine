#pragma once

namespace Eclipse
{
	template<typename T>
	class AssetImporterStrategy
	{
	public:
		virtual void ImportAsset(T& outData, const char* path) = 0;
	};
}