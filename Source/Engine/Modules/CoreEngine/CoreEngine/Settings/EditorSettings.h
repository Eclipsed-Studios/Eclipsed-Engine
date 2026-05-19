#pragma once

#include <vector>
#include <string>

#include "SettingsBase.hpp"
#include "CoreEngine/Math/Vector/Vector2.h"

namespace Eclipse::Settings
{
	struct OpenEditorWindows
	{
		int ID;
		std::string Name;

		SERIALIZE(
			MAKE_NVP(ID),
			MAKE_NVP(Name)
		)
	};

	struct EditorSettings : public BaseSettings<EditorSettings>
	{
		SETTINGS_DATA{
			std::string LastActiveScene = "";
			std::vector<OpenEditorWindows> CurrentlyOpenEditorWindows;
			bool OpenLastOpenSceneOnStartup = true;

			SERIALIZE(
				MAKE_NVP(LastActiveScene),
				MAKE_NVP(CurrentlyOpenEditorWindows),
				MAKE_NVP(OpenLastOpenSceneOnStartup)
			)
		};

		static const decltype(Data::LastActiveScene)& GetLastActiveScene() {
			return GetData().LastActiveScene;
		} static void SetLastActiveScene(const decltype(Data::LastActiveScene)& data) {
			GetData().LastActiveScene = data;
		};
		GET_SET(CurrentlyOpenEditorWindows);
		GET_SET(OpenLastOpenSceneOnStartup);

		EditorSettings() = default; ~EditorSettings() = default; struct TEMP {
			TEMP() {
				Eclipse::EventSystem::Subscribe("Engine-Load", EditorSettings::Load); Eclipse::EventSystem::Subscribe("Engine-Shutdown", EditorSettings::Save);
			}
		}; static inline TEMP temp = {}; static inline EditorSettings::Data& GetData() {
			static EditorSettings::Data data{}; return data;
		} static constexpr const char* Name = "editor"; static constexpr const char* SettingsName() {
			return EditorSettings::Name;
		};
	};
}