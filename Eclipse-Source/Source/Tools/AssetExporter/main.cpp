#include "AssetEngine/Editor/Importer/EditorAssetImporter.h"
#include "AssetEngine/Resources.h"
#include "AssetEngine/Assets/Texture.h"
#include "AssetEngine/Assets/Material.h"

int main()
{
	Eclipse::EditorAssetImporter::ImportAll("F:/Projects/Eclipsed-Engine/RPS-Project/Project/Assets");
	Eclipse::Material material = Eclipse::Resources::Get<Eclipse::Material>("05e7fe3b238cf9de4a7879b89fdec409");


	//Eclipse::EditorAssetImporter::Import("F:/Projects/Eclipsed-Engine/RPS-Project/Project/Assets/Test/noah1.jpg");

	//Eclipse::EditorAssetImporter::Import("F:/Projects/Eclipsed-Engine/RPS-Project/Project/Assets/Test/DefaultSprite.pglsl");
	//Eclipse::EditorAssetImporter::Import("F:/Projects/Eclipsed-Engine/RPS-Project/Project/Assets/Test/DefaultSprite.vglsl");

	//Eclipse::EditorAssetImporter::Import("F:/Projects/Eclipsed-Engine/RPS-Project/Project/Assets/Test/DefaultMaterial.mat");


	return 0;
}