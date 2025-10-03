//
// Created by kitaS24 on 20.08.2025.
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

class Player: public Ent{

    Vec3 CamRotVecInternal = {0,0,0};

    //
    void MoveXZ(Vec3 HSize,Vec3 V){
        Vec3 V20th = Vec3Divide(V,{20,20,20});
        if(CollisionWorldArea(Brushes,Engine_Max_Brushes,Vec3Add(Pos,V),Vec3Add(HSize,{100,100,100}))) {
            for (int x = 0; x < 20; ++x) {
                Pos = Vec3Add(Pos, {V20th.X, 0, 0});
                if (CollisionWorldArea(Brushes, Engine_Max_Brushes, Pos, HSize)) {
                    Pos = Vec3Subtract(Pos, {V20th.X, 0, 0});
                    Vel.X = 0;
                    break;
                }
            }
        }else{
            Pos = Vec3Add(Pos,{V.X,0,0});
        }
        if(CollisionWorldArea(Brushes,Engine_Max_Brushes,Vec3Add(Pos,V),Vec3Add(HSize,{100,100,100}))) {
            for (int z = 0; z < 20; ++z) {
                Pos = Vec3Add(Pos, {0, 0, V20th.Z});
                if (CollisionWorldArea(Brushes, Engine_Max_Brushes, Pos, HSize)) {
                    Pos = Vec3Subtract(Pos, {0, 0, V20th.Z});
                    Vel.Z = 0;
                    break;
                }
            }
        }else{
            Pos = Vec3Add(Pos,{0,0,V.Z});
        }
    }
    void MoveY(Vec3 HSize,Vec3 V){
        Vec3 V20th = Vec3Divide(V,{20,20,20});
        if(CollisionWorldArea(Brushes,Engine_Max_Brushes,Vec3Add(Pos,V),Vec3Add(HSize,{100,100,100}))) {
            for (int x = 0; x < 20; ++x) {
                Pos = Vec3Add(Pos, {0, V20th.Y, 0});
                if (CollisionWorldArea(Brushes, Engine_Max_Brushes, Pos, HSize)) {
                    Pos = Vec3Subtract(Pos, {0, V20th.Y, 0});
                    Vel.Y = 0;
                    break;
                }
            }
        }else{
            Pos = Vec3Add(Pos,{0,V.Y,0});
        }
    }
    //
    std::string GetDebugName() override {
        return "Player";
    }
    void CreateVarWindow(int cId,Vec2I W) override {
        ImGui::Begin((GetDebugName()+"##"+std::to_string(cId)).c_str());
        ImGui::SetWindowPos(ImVec2(0,W.Y-200));
        ImGui::SetWindowSize(ImVec2(200,200));
        ImGui::Text("player");
        ImGui::Text(("Vel:"+std::to_string(MagVec3(Vel))).c_str());
        ImGui::Text(std::to_string(Vel.X).c_str());
        ImGui::Text(std::to_string(Vel.Y).c_str());
        ImGui::Text(std::to_string(Vel.Z).c_str());

        if(ImGui::Button("Fire Light")){
            Ent* Light = GetEntByName(*Ents,"player light");
            if(Light){
                Light->OnFire(nullptr,Self);
            }
        }

        ImGui::End();
    }

    float Think(float TPS) override{
        float PlayerSpeed = 3600;//run=6080,crouch=1200
        float PlayerAccSpeed = 7000;
        Vec3 KDir = {};
        Vec3 PlayerSize = {405,915,405};
        Vec2 MouseOffset = {0,0};
        if((*UserKeyBind).key('W')){
            KDir = Vec3Add(KDir,{0,0,1});
        }
        if((*UserKeyBind).key('S')){
            KDir = Vec3Add(KDir,{0,0,-1});
        }
        if((*UserKeyBind).key('A')){
            KDir = Vec3Add(KDir,{-1,0,0});
        }
        if((*UserKeyBind).key('D')){
            KDir = Vec3Add(KDir,{1,0,0});
        }

        if(glfwGetKey((*Display).window,GLFW_KEY_LEFT)){
            Rot.Y = Rot.Y + 90.0f/TPS;
        }
        if(glfwGetKey((*Display).window,GLFW_KEY_RIGHT)){
            Rot.Y = Rot.Y - 90.0f/TPS;
        }
        if(glfwGetKey((*Display).window,GLFW_KEY_UP)){
            Rot.X = Rot.X + 90.0f/TPS;
        }
        if(glfwGetKey((*Display).window,GLFW_KEY_DOWN)){
            Rot.X = Rot.X - 90.0f/TPS;
        }

        if(!((*Mouse).GetInMenu())){
            //(*Mouse).SetInMenu();
            MouseOffset = (*Mouse).GetCenteredMouse(true);//(*Mouse).GetMousePos();
            //std::cout <<  MouseOffset.X<<"|"<< MouseOffset.Y<<"\n";
            Rot.Y = Rot.Y - MouseOffset.X;
            Rot.X = Rot.X - MouseOffset.Y;
            if (Rot.X > 90) {
                Rot.X = 90;
            }
            if (Rot.X < -90) {
                Rot.X = -90;
            }
        }

        if((*UserKeyBind).key('E')){
            ChangeMap("saves/test1.gems",true);
            std::cout << WorldRaycast(Pos, Vec3Add(Pos, Vec3Multiply(CamRotVecInternal,{100000,100000,100000})),{10,10,10},300,Brushes)<<"\n";
        }

        KDir = NormaliseVec3(KDir);
        KDir = rotatePoint(KDir,{0,-Rot.Y,-Rot.Z});
        CamRotVecInternal =  rotatePoint({0,0,1},{-Rot.X,-Rot.Y,-Rot.Z});
        KDir = Vec3Multiply(KDir,{PlayerAccSpeed/TPS,PlayerAccSpeed/TPS,PlayerAccSpeed/TPS});
        Vel = Vec3Add(Vel,KDir);
        if(MagVec3({Vel.X,0,Vel.Z}) >PlayerSpeed){
            Vec3 NVel = NormaliseVec3({Vel.X,0,Vel.Z});
            NVel = Vec3Multiply(NVel,{PlayerSpeed,PlayerSpeed,PlayerSpeed});
            Vel = {NVel.X,Vel.Y,NVel.Z};
        }

        if(CollisionWorldArea(Brushes, Engine_Max_Brushes, Vec3Add(Pos,{0,-5,0}), PlayerSize)) {
            if ((*UserKeyBind).key(' ')) {
                Pos.Y = Pos.Y + 10;
                Vel.Y = Vel.Y + 3500;
            }
            if(MagVec3(KDir) ==0) {
                if (MagVec3({Vel.X, 0, Vel.Z}) < 25000 / TPS) {
                    Vel.X = 0;
                    Vel.Z = 0;
                } else {
                    float D = MagVec3({Vel.X, 0, Vel.Z});
                    Vec3 NVel = NormaliseVec3({Vel.X, 0, Vel.Z});
                    NVel = Vec3Multiply(NVel, {D - (25000 / TPS), D - (25000 / TPS), D - (25000 / TPS)});
                    Vel = {NVel.X,Vel.Y,NVel.Z};
                }
            }
        }else {
            Vel.Y = Vel.Y + Engine_G / TPS;

                if (MagVec3({Vel.X, 0, Vel.Z}) < 1000 / TPS) {
                    if(MagVec3(KDir) ==0) {
                        Vel.X = 0;
                        Vel.Z = 0;
                    }
                } else {
                    float D = MagVec3({Vel.X, 0, Vel.Z});
                    Vec3 NVel = NormaliseVec3({Vel.X, 0, Vel.Z});
                    NVel = Vec3Multiply(NVel, {D - (1000 / TPS), D - (1000 / TPS), D - (1000 / TPS)});
                    Vel = {NVel.X,Vel.Y,NVel.Z};
                }
        }

        MoveXZ(PlayerSize,{Vel.X/TPS,Vel.Y/TPS,Vel.Z/TPS});
        MoveY(PlayerSize,{0,Vel.Y/TPS,0});


        return 0;
    }
    void PreRender() override{
        //3d frame
        *CamPos = Pos;
        *CamRot = Rot;
        *CamRotVec = CamRotVecInternal;
        glRotatef(Rot.X,1,0,0);
        glRotatef(Rot.Y,0,1,0);

        glTranslatef(-Pos.X,-Pos.Y,-Pos.Z);
    }

    void Save(std::ofstream &File) override{
        File.write(reinterpret_cast<char *>(&Pos), sizeof(Pos));
        File.write(reinterpret_cast<char *>(&Vel), sizeof(Vel));
        File.write(reinterpret_cast<char *>(&Rot), sizeof(Rot));
    }
    void Load(std::ifstream &File) override{
        File.read(reinterpret_cast<char *>(&Pos), sizeof(Pos));
        File.read(reinterpret_cast<char *>(&Vel), sizeof(Vel));
        File.read(reinterpret_cast<char *>(&Rot), sizeof(Rot));
    }
};