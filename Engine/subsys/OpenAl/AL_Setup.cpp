//
// Created by kitaS24 on 31.08.2025.
//

/*
    Engine7 - a GoldSrc like engine
    Copyright (C) 2025  kitaS24

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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