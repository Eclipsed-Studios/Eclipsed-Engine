#pragma once

namespace Eclipse::Files
{
	class JsonDocument final
	{
	public:
		JsonDocument(const char* aJsonPath);
		~JsonDocument() = default;

	public:
		void Load(const char* aJsonPath);


	};
}