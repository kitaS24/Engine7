//
// Created by kitaS24 on 31.08.2025.
//

class OpenAl{
private:
    //openal

    ALCcontext* AlContext = nullptr;
    ALCdevice* AlDevice = nullptr;
public:
    void Setup(){
        //creating output
        AlDevice = alcOpenDevice(nullptr);
        if (!AlDevice) {
            std::cout << "Failed to open device.\n";
            exit(-1);
        }

        AlContext = alcCreateContext(AlDevice, nullptr);
        alcMakeContextCurrent(AlContext);
        if (!AlContext) {
            std::cout << "Failed to create context.\n";
            exit(-1);
        }
        //setup
        alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
        alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
        float orientation[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };
        alListenerfv(AL_ORIENTATION, orientation);
    }
    void SetListener(Vec3 Pos,Vec3 LookVec,bool InvertDir){
        //setting look vector
        float Player[] =
                {LookVec.X, LookVec.Y, LookVec.Z
                        ,0,1,0};
        if(InvertDir){
            Player[0] =  -LookVec.X;
            Player[1] =  -LookVec.Y;
            Player[2] =  -LookVec.Z;
        }
        //setting pos and LookVec
        alListenerfv(AL_ORIENTATION, Player);

        alListener3f(AL_POSITION, Pos.X/1000, Pos.Y/1000, Pos.Z/1000);
    }
    void Cleanup(){
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(AlContext);
        alcCloseDevice(AlDevice);
    }
};
/*
void SetupOpenAl(ALCcontext*& context,ALCdevice*& device){
    device = alcOpenDevice(nullptr);
    if (!device) {
        std::cout << "Failed to open device.\n";
        exit(-1);
    }

    context = alcCreateContext(device, nullptr);
    alcMakeContextCurrent(context);
    if (!context) {
        std::cout << "Failed to create context.\n";
        exit(-1);
    }
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    float orientation[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };
    alListenerfv(AL_ORIENTATION, orientation);
}

void CleanupOpenAl(ALCcontext*& context,ALCdevice*& device){
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}
 */
void checkError(const std::string& msg) {
    ALenum err = alGetError();
    if (err != AL_NO_ERROR) {
        std::cerr << "[OpenAL ERROR] " << msg << ": " << err << "\n";
    }
}