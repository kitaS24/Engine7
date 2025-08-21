//
// Created by kitaS24 on 21.08.2025.
//

class Particle: public Ent{

    //Vec3 Color = {0.8,1,1};
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
        //ImGui::ColorEdit3("Light Color",&Color.X);
        //ImGui::SliderFloat("light Brightness",&Br,0,20);
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
};