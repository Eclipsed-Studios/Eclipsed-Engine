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

	class Material final
	{
		ASSET_OPERATORS_DEF(Material, Assets::MaterialHandle, Assets::MaterialManager);

	public:
		Texture& GetTexture();
		const Texture& GetTexture() const;

		VertexShader& GetVertexShader();
		const VertexShader& GetVertexShader() const;

		PixelShader& GetPixelShader();
		const PixelShader& GetPixelShader() const;

		unsigned GetShaderProgramID() const;

	public:
		void BindTexture();
		void BindShader();
		void BindColor();

		void Use();
		void Create();

		static inline const char* colorID = "material.color";

	};
}