#pragma once

#include "Asset.h"

#include "Texture.h"
#include "VertexShader.h"
#include "PixelShader.h"

namespace Eclipse
{
	namespace Assets
	{
		struct MaterialHandle;
		class MaterialManager;
	}

	class Materials final
	{
		ASSET_OPERATORS_DEF(Materials, Assets::MaterialHandle, Assets::MaterialManager);

	public:
		Textures& GetTexture();
		const Textures& GetTexture() const;

		VertexShaders& GetVertexShader();
		const VertexShaders& GetVertexShader() const;

		PixelShaders& GetPixelShader();
		const PixelShaders& GetPixelShader() const;

		unsigned GetShaderProgramID() const;

	public:
		void BindTexture();
		void BindShader();
		void BindColor();

		void Use();
		void Create();
	};
}