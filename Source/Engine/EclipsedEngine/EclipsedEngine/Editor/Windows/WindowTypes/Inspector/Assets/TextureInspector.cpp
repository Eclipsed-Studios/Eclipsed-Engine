#include "TextureInspector.h"

#include "AssetEngine/Core/SupportedAssets.h"
#include "ImGui/ImGui.h"

#include "EclipsedEngine/Editor/Windows/WindowTypes/SpriteEditor.h"
#include "AssetEngine/Core/EditorAssetDatabase.h"
#include "AssetEngine/Metadata/Data/TextureMeta.h"
#include "CoreEngine/MainSingleton.h"
namespace Eclipse::Editor
{
	bool TextureInspector::CanInspect(const InspectableTarget& target)
	{
		if (!std::holds_alternative<AssetTarget>(target)) return false;

		AssetTarget asset = std::get<AssetTarget>(target);
		return Assets::GetAssetTypeFromExtension(asset.extension().string()) == Assets::AssetType::Texture;
	}

	void TextureInspector::Draw(const InspectableTarget& target)
	{
		AssetTarget asset = std::get<AssetTarget>(target);

		Assets::AssetDatabase& database = MainSingleton::GetInstance<Assets::AssetDatabase>();
		Assets::GUID guid = database.GetGUIDFromFullPath(asset);

		if (ImGui::Button("Open in sprite editor"))
			SpriteEditor::SetTexture(guid);
	}
}