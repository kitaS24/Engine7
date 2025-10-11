//
// Created by kitaS24 on 31.08.2025.
//

// Copyright (c) 2025 kitaS24

// WAV header struct **UNCOMPRESSED**
struct WavPcmHeader {
    char riff[4];
    unsigned int size;
    char wave[4];             // "WAVE"
    char fmt[4];
    unsigned int fmtSize;
    unsigned short format;    // 1 (PCM)
    unsigned short channels;
    unsigned int sampleRate;
    unsigned int byteRate;
    unsigned short blockAlign;
    unsigned short bitsPerSample;
    char data[4];
    unsigned int dataSize;
};


class SoundEngineSource {

    //loading WAV
    bool LoadWAV(const std::string &filename, ALuint &outBuffer, float &outPlayTime) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Failed to open file " << filename << "\n";
            return false;
        }

        //getting header
        WavPcmHeader header;
        file.read(reinterpret_cast<char *>(&header), sizeof(WavPcmHeader));
        if (std::strncmp(header.riff, "RIFF", 4) != 0 || std::strncmp(header.wave, "WAVE", 4) != 0) {
            std::cerr << "Not a valid WAV file.\n";
            return false;
        }
        if (header.format != 1) {
            std::cerr << "Only PCM WAV supported.\n";
            return false;
        }

        char *audioData = new char[header.dataSize];
        file.read(reinterpret_cast<char *>(audioData), header.dataSize);//getting Data
        if (!file) {
            std::cerr << "Failed to read WAV audio data.\n";
            delete[] audioData;
            return false;
        }

        outPlayTime = float(header.dataSize) / float(header.byteRate);

        //copying to OpenAl,freeing mem
        ALenum format = 0;
        if (header.channels == 1) {
            format = (header.bitsPerSample == 8) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
        } else if (header.channels == 2) {
            format = (header.bitsPerSample == 8) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
        } else {
            std::cerr << "Unsupported channel count: " << header.channels << "\n";
            delete[] audioData;
            return false;
        }

        alGenBuffers(1, &outBuffer);
        if (alGetError() != AL_NO_ERROR) {
            std::cerr << "Failed to generate OpenAL buffer.\n";
            delete[] audioData;
            return false;
        }

        alBufferData(outBuffer, format, audioData, static_cast<ALsizei>(header.dataSize), header.sampleRate);
        checkError("alBufferData");
        if (alGetError() != AL_NO_ERROR) {
            std::cerr << "Failed to buffer audio data.\n";
            alDeleteBuffers(1, &outBuffer);
            delete[] audioData;
            return false;
        }

        delete[] audioData;
        return true;
    }

    Vec3 Source;
    bool IsSoundLoaded;
    float Volume;
    float PlayTime;
    //OpenAl
    ALuint bufferID;
    ALuint AlSource;

public:

    void Setup(Vec3 P){
        alGenSources(1, &AlSource);
        Source = Vec3Divide(P,{1000,1000,1000});
    }
    void UpdatePos(Vec3 P){
        Source = Vec3Divide(P,{1000,1000,1000});
        alSource3i(AlSource, AL_POSITION, Source.X, Source.Y, Source.Z);
    }
    void UpdateSpeed(float Speed){
        alSourcef(AlSource, AL_PITCH, Speed);
    }
    void UnloadSound(){
        if(!IsSoundLoaded){return;}
        alDeleteBuffers(1,&bufferID);
        IsSoundLoaded = false;
    }
    void Pause(){
        alSourceStop(AlSource);
    }
    void Delete(){
        alSourceStop(AlSource);
        alDeleteSources(1,&AlSource);
        UnloadSound();
    }
    bool LoadWavSound(std::string filename,float Vol){
        Volume = Vol;
        return LoadWAV(filename,bufferID,PlayTime);
    }
    void Play(float SoundVolume){

        alSourcei(AlSource, AL_SOURCE_RELATIVE, AL_FALSE); //3D sound
        alSource3i(AlSource, AL_POSITION, Source.X, Source.Y, Source.Z);

        alSourcei(AlSource, AL_BUFFER, bufferID);
        alSourcef(AlSource, AL_GAIN, SoundVolume*Volume);  // Volume
        alSourcef(AlSource, AL_PITCH, 1.0f); // Playback speed

        alSourcePlay(AlSource);

    }

};