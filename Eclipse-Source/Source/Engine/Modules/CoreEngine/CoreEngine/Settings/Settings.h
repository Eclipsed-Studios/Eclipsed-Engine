#pragma once

#include <string>
#include "rapidjson/document.h"

namespace Eclipse
{
	class HejsanKOmis
	{
	public:
		HejsanKOmis(const char* path);
		~HejsanKOmis();

	public:
		void Save();

	public:
		template<typename T>
		T Get(const char* key);

		template<typename T>
		void Set(const char* key, T& value);

	protected:
		rapidjson::Document doc;
		std::string relPath = "";

		bool fileOpenend = false;
	};
}

#include "Settings.inl"