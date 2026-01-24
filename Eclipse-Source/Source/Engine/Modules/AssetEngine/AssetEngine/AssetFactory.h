#pragma once

namespace Eclipse::Assets
{
	struct MaterialData {
		size_t Texture = 0;
		size_t VertexShader = 0;
		size_t PixelShader = 0;
		Math::Color Color = { 1.f, 1.f, 1.f, 1.f };

		SERIALIZE(MAKE_NVP(Texture),
			MAKE_NVP(VertexShader),
			MAKE_NVP(PixelShader),
			MAKE_NVP(Color))
	};

	class AssetFactory final
	{
	public:
		static void CreateMaterial(const char* path);
	};
}