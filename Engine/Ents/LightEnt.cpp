//
// Created by kitaS24 on 19.08.2025.
//

class Light: public Ent{

    //Vec3 Color = {0.8,1,1};
    Vec3 Color = {int(rand()%1000)/1000.0f,int(rand()%1000)/1000.0f,int(rand()%1000)/1000.0f};
    float Br = 8;
    int CustomT = rand()%1000;
    int ThinkTimes = 0;

    std::string GetDebugName() override {
        return "Light";
    }
    void CreateVarWindow(int cId,Vec2I W) override {
        ImGui::Begin((GetDebugName()+"##"+std::to_string(cId)).c_str());
        ImGui::SetWindowPos(ImVec2(0,W.Y-200));
        ImGui::SetWindowSize(ImVec2(200,200));
        ImGui::Text("light entity");
        ImGui::ColorEdit3("Light Color",&Color.X);
        ImGui::SliderFloat("light Brightness",&Br,0,20);
        ImGui::End();
    }

    void PreRender() override{
        Vec3 Rot = rotatePoint({0,3500,0},{(Time+CustomT)*2*2,(Time+CustomT)*9*2,(Time+CustomT)*3*2});
        //Vec3 Rot = {0,3500,0};
        AddLight(LightsPtr, Vec3Add(Pos,Rot),{Color.X*Br,Color.Y*Br,Color.Z*Br});
    }
    void Render3D() override{
        Vec3 Rot = rotatePoint({0,3500,0},{(Time+CustomT)*2*2,(Time+CustomT)*9*2,(Time+CustomT)*3*2});
        glColor3ub(255,0,0);
        glPointSize(4);
        glBegin(GL_POINTS);
        glVertex3f(Pos.X+Rot.X,Pos.Y+Rot.Y,Pos.Z+Rot.Z);
        glEnd();
    }
    float Think(float TPS) override{
        //ThinkTimes = ThinkTimes+1;
        //if(ThinkTimes >1){
        //    KillSelf();
        //}
        return 10;
    }

    void Save(std::ofstream &File) override{
        File.write(reinterpret_cast<char *>(&CustomT), sizeof(CustomT));
        File.write(reinterpret_cast<char *>(&Color), sizeof(Color));
        File.write(reinterpret_cast<char *>(&Br), sizeof(Br));
    }
    void Load(std::ifstream &File) override{
        File.read(reinterpret_cast<char *>(&CustomT), sizeof(CustomT));
        File.read(reinterpret_cast<char *>(&Color), sizeof(Color));
        File.read(reinterpret_cast<char *>(&Br), sizeof(Br));
    }

};