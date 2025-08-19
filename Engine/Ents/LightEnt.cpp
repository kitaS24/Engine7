//
// Created by kitaS24 on 19.08.2025.
//

class Light: public Ent{

    Vec3 Color = {0.8,1,1};
    float Br = 60;
    int CustomT = rand()%1000;

    std::string GetDebugName() override {
        return "Light";
    }
    void CreateVarWindow(int cId,Vec2I W) override {
        ImGui::Begin((GetDebugName()+"##"+std::to_string(cId)).c_str());
        ImGui::SetWindowPos(ImVec2(0,W.Y-200));
        ImGui::SetWindowSize(ImVec2(200,200));
        ImGui::Text("light entity");
        ImGui::ColorEdit3("Light Color",&Color.X);
        ImGui::SliderFloat("light Brightness",&Br,0,100);
        ImGui::End();
    }

    void PreRender() override{
        Vec3 Rot = rotatePoint({0,35,0},{(Time+CustomT)*2,(Time+CustomT)*9,(Time+CustomT)*3});
        AddLight(LightsPtr, Vec3Add(Pos,Rot),{Color.X*Br,Color.Y*Br,Color.Z*Br});
    }
};