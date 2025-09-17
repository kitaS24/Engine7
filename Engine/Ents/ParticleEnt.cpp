//
// Created by kitaS24 on 21.08.2025.
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

class Particle: public Ent{

    Vec3 Color = {int(rand()%1000)/1000.0f,int(rand()%1000)/1000.0f,int(rand()%1000)/1000.0f};
    float Br = 4;
    int CustomT = rand()%1000;
    int ThinkTimes = 0;
    float T = 0;

    Vec3 ParticlePos[8] = {};
    Vec3 ParticleVel[8] = {};

    std::string GetDebugName() override {
        return "Particle";
    }
    void CreateVarWindow(int cId,Vec2I W) override {
        ImGui::Begin((GetDebugName()+"##"+std::to_string(cId)).c_str());
        ImGui::SetWindowPos(ImVec2(0,W.Y-200));
        ImGui::SetWindowSize(ImVec2(200,200));
        ImGui::Text("particle system");
        ImGui::End();
    }
    float Think(float TPS) override{
        Pos = {0,1100,0};
        T = T+(1.0f/TPS);
        if(T >2){
            T = 0;
            for (int i = 0; i < 8; ++i) {
                ParticlePos[i] = {(rand()%2000-1000)/10.0f+Pos.X,Pos.Y,(rand()%2000-1000)/10.0f+Pos.Z};
                ParticleVel[i] = {(rand()%2000-1000)/5.0f,5000,(rand()%2000-1000)/5.0f};
            }
        }
        for (int i = 0; i < 8; ++i) {
            ParticlePos[i] = Vec3Add(ParticlePos[i], Vec3Divide(ParticleVel[i],{TPS,TPS,TPS}));
            ParticleVel[i].Y = ParticleVel[i].Y +Engine_G/TPS;
        }
        return 0;
    }
    void Render3D() override{

        unsigned int LightsN = 0;
        for (int i = 0; i < Engine_Max_Lights; ++i) {
            if(!(*LightsPtr).enabled[i]){
                LightsN = i;
                break;
            }
        }
        if(LightsN >512){
            LightsN = 512;
        }
        RenderParticle(ParticlePos,8,{-(*CamRot).X,-(*CamRot).Y,-(*CamRot).Z},{50,50},Materials+2,LightsPtr,LightsN,*CamPos,{255,255,255,255*(1-(T/2))});
    }

    void ShadowPass(Vec3 LightPos,Vec3 LightSize,Vec3 LightDir,GLuint Shader) override{
        ShadowRenderParticle(ParticlePos,8,{-(*CamRot).X,-(*CamRot).Y,-(*CamRot).Z},{50,50},Shader,LightPos,LightSize,LightDir);
    }

    void Save(std::ofstream &File) override{
        File.write(reinterpret_cast<char *>(&Pos), sizeof(Pos));
        File.write(reinterpret_cast<char *>(&ParticlePos), sizeof(ParticlePos));
        File.write(reinterpret_cast<char *>(&ParticleVel), sizeof(ParticleVel));
        File.write(reinterpret_cast<char *>(&Rot), sizeof(Rot));
        File.write(reinterpret_cast<char *>(&T), sizeof(T));
    }
    void Load(std::ifstream &File) override{
        File.read(reinterpret_cast<char *>(&Pos), sizeof(Pos));
        File.read(reinterpret_cast<char *>(&ParticlePos), sizeof(ParticlePos));
        File.read(reinterpret_cast<char *>(&ParticleVel), sizeof(ParticleVel));
        File.read(reinterpret_cast<char *>(&Rot), sizeof(Rot));
        File.read(reinterpret_cast<char *>(&T), sizeof(T));
    }
};