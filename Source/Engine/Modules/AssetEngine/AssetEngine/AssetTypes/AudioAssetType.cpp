#include "AudioAssetType.h"

#include "fmod/fmod.hpp"
#include "CoreEngine/MainSingleton.h"

#include "AssetEngine/MetaData/Data/AudioMeta.h"

namespace Eclipse::Assets
{
	ImportedData AudioAssetType::Import(const AssetMeta& file)
	{
		ImportedAudio audio;

		FMOD::Sound* sound = nullptr;

		FMOD::System* system = MainSingleton::GetRaw<FMOD::System*>();

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

		audio.FrameCount = (len1 + len2) / (audio.Channels * sizeof(short));

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

		writer.Write(DATA_SIZE_PAIR(_data.Storage));
		writer.Write(DATA_SIZE_PAIR(_data.Format));
		writer.Write(DATA_SIZE_PAIR(_data.SampleRate));
		writer.Write(DATA_SIZE_PAIR(_data.FrameCount));
		writer.Write(DATA_SIZE_PAIR(_data.Channels));
		writer.Write(DATA_SIZE_PAIR(_data.Streaming));

		const size_t size = _data.Data.size();
		writer.Write(&size, sizeof(size_t));
		writer.Write(_data.Data.data(), size);
	}

	void AudioAssetType::Load(BinaryReader& reader, const AssetMeta& meta, AssetData* data)
	{
		AudioData* _data = reinterpret_cast<AudioData*>(data);

		reader.Read(DATA_SIZE_PAIR(_data->Storage));
		reader.Read(DATA_SIZE_PAIR(_data->Format));
		reader.Read(DATA_SIZE_PAIR(_data->SampleRate));
		reader.Read(DATA_SIZE_PAIR(_data->FrameCount));
		reader.Read(DATA_SIZE_PAIR(_data->Channels));
		reader.Read(DATA_SIZE_PAIR(_data->Streaming));

		size_t size;
		reader.Read(&size, sizeof(size_t));
		_data->Data.resize(size);
		_data->guid = meta.guid;

		reader.Read(_data->Data.data(), size);



		FMOD_CREATESOUNDEXINFO exinfo{};
		exinfo.cbsize = sizeof(exinfo);
		exinfo.length = static_cast<unsigned int>(size);
		exinfo.numchannels = _data->Channels;
		exinfo.defaultfrequency = _data->SampleRate;

		switch (_data->Format)
		{
		case AudioFormat::PCM16: 
			exinfo.format = FMOD_SOUND_FORMAT_PCM16;
			break;
		case AudioFormat::PCM32F:
			exinfo.format = FMOD_SOUND_FORMAT_PCMFLOAT;
			break;
		}

		FMOD::System* system = MainSingleton::GetRaw<FMOD::System*>();

		FMOD_MODE mode = FMOD_OPENMEMORY | FMOD_OPENRAW;

		FMOD_RESULT result = system->createSound(
			reinterpret_cast<const char*>(_data->Data.data()),
			mode,
			&exinfo,
			&_data->sound
		);
	}

	void AudioAssetType::LoadFromBinary(BinaryReader& reader, const AssetMeta& meta, AssetData* data)
	{
		AudioData* _data = reinterpret_cast<AudioData*>(data);

		data->guid = meta.guid;
		reader.SetRead(meta.offset);

	}
}