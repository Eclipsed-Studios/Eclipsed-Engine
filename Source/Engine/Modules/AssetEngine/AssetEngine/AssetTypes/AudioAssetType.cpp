#include "AudioAssetType.h"

#include "fmod/fmod.hpp"
#include "CoreEngine/MainSingleton.h"

namespace Eclipse::Assets
{
    ImportedData AudioAssetType::Import(const AssetMeta& file)
    {
        ImportedAudio audio;

        FMOD::Sound* sound = nullptr;

        FMOD::System* system = MainSingleton::GetInstance<FMOD::System*>();
        system->createSound(
            file.fullPath.generic_string().c_str(),
            FMOD_DEFAULT | FMOD_CREATESAMPLE,
            nullptr,
            &sound
        );

        unsigned length = 0;
        sound->getLength(&length, FMOD_TIMEUNIT_PCMBYTES);


        FMOD_SOUND_FORMAT format;
        int channels;
        int bits;

        sound->getFormat(nullptr, &format, &channels, &bits);


        float frequency;
        sound->getDefaults(&frequency, nullptr);
        
        switch (format)
        {
        case FMOD_SOUND_FORMAT_PCM16:
            audio.Format = AudioFormat::PCM16;
            audio.Storage = AudioStorage::PCM;
            break;

        case FMOD_SOUND_FORMAT_PCMFLOAT:
            audio.Format = AudioFormat::PCM32F;
            audio.Storage = AudioStorage::PCM;
            break;

        default:
            audio.Storage = AudioStorage::Compressed;
            break;
        }



        audio.SampleRate = static_cast<uint32_t>(frequency);
        audio.Channels = static_cast<uint16_t>(channels);

        void* ptr1 = nullptr;
        void* ptr2 = nullptr;
        unsigned int len1 = 0;
        unsigned int len2 = 0;

        sound->lock(
            0,
            length,
            &ptr1, &ptr2,
            &len1, &len2
        );

        audio.FrameCount = (len1 + len2) /(audio.Channels * sizeof(short));

        audio.Data.resize(len1 + len2);

        memcpy(audio.Data.data(), ptr1, len1);

        if (ptr2 && len2 > 0)
        {
            memcpy(audio.Data.data() + len1, ptr2, len2);
        }

        sound->unlock(ptr1, ptr2, len1, len2);

        sound->release();


        return audio;
    }

    ProcessedData AudioAssetType::Process(const ImportedData& file)
    {
        return file;
    }

    void AudioAssetType::Serialize(BinaryWriter& writer, const ProcessedData& data)
    {
        if (!writer.IsOpen()) return;

        const ImportedAudio& _data = std::get<ImportedAudio>(data);

        writer.Write(WRITE(_data.Storage));
        writer.Write(WRITE(_data.Format));
        writer.Write(WRITE(_data.SampleRate));
        writer.Write(WRITE(_data.FrameCount));
        writer.Write(WRITE(_data.Channels));
        writer.Write(WRITE(_data.Streaming));
        writer.Write(_data.Data.data(), _data.Data.size());
    }

    RuntimeAsset AudioAssetType::Load(BinaryReader& reader, const AssetMeta& meta)
    {
        return RuntimeAsset();
    }
}