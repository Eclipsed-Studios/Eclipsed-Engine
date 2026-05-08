#pragma once

#include <vector>
#include <variant>

#include "AssetEngine/Core/GUID.h"

namespace Eclipse::Assets
{
#pragma region AUDIO

    enum class AudioStorage
    {
        PCM,
        Compressed
    };

    enum class AudioFormat
    {
        PCM16,
        PCM32F,
        OGG,
        WAV,
        MP3
    };

    struct ImportedAudio
    {
        AudioStorage Storage = AudioStorage::PCM;
        AudioFormat Format = AudioFormat::PCM16;

        unsigned int SampleRate = 0;
        unsigned int FrameCount = 0;
        int Channels = 0;

        bool Streaming = false;

        std::vector<unsigned char> Data;
    };

#pragma endregion

#pragma region FONT

    struct ImportedFont
    {
        std::vector<unsigned char> Data;
    };

#pragma endregion

#pragma region MATERIAL

    struct ImportedMaterial {
        GUID textureID;
        GUID vertexShaderID;
        GUID pixelShaderID;
    };

#pragma endregion

#pragma region TEXTURE

    struct ImportedTexture{
        int width;
        int height;
        int channels;
        std::vector<unsigned char> Data;
    };

#pragma endregion


    using ImportedData = std::variant<
        ImportedAudio,
        ImportedFont,
        ImportedMaterial,
        ImportedTexture
    >;

    using ProcessedData = ImportedData;
}