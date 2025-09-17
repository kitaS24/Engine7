//
// Created by kitaS24 on 19.08.2025.
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

//THIS IS AN EXAMPLE

class Light: public Ent{

    //setting RGB,Brightness
    Vec3 Color = {0,0,0};
    Vec3 Dir = {};
    float InnerCone = 180;
    float OuterCone = 20;
    float Br = 8;
    int CustomT = rand()%1000;
    int ThinkTimes = 0;

    //setts debug name/ent name
    std::string GetDebugName() override {
        return "Light";
    }
    //gui
    void CreateVarWindow(int cId,Vec2I W) override {
        ImGui::Begin((GetDebugName()+"##"+std::to_string(cId)).c_str());
        ImGui::SetWindowPos(ImVec2(0,W.Y-200));
        ImGui::SetWindowSize(ImVec2(200,200));
        ImGui::Text("light entity");
        ImGui::ColorEdit3("Light Color",&Color.X);
        ImGui::SliderFloat("light Brightness",&Br,0,20);

        ImGui::SliderFloat("Rot X",&Dir.X,180,-180);
        ImGui::SliderFloat("Rot Y",&Dir.Y,180,-180);
        ImGui::SliderFloat("Rot Z",&Dir.Z,180,-180);

        ImGui::SliderFloat("InnerCone",&InnerCone,0,180);
        ImGui::SliderFloat("OuterCone",&OuterCone,0,180);
        ImGui::End();
    }
    //adds light into the scene
    void PreRender() override{
        AddLight(LightsPtr, Pos,{Color.X*Br,Color.Y*Br,Color.Z*Br}, rotatePoint({0,-1,0},Dir),InnerCone,OuterCone);
    }
    //renders dot on the ent pos
    void Render3D() override{
        glColor3ub(255,0,0);
        glPointSize(4);
        glBegin(GL_POINTS);
        glVertex3f(Pos.X,Pos.Y,Pos.Z);
        glEnd();
    }

    //saving light from save file
    void Save(std::ofstream &File) override{
        File.write(reinterpret_cast<char *>(&CustomT), sizeof(CustomT));
        File.write(reinterpret_cast<char *>(&Color), sizeof(Color));
        File.write(reinterpret_cast<char *>(&Br), sizeof(Br));
    }
    //loading light from save file
    void Load(std::ifstream &File) override{
        File.read(reinterpret_cast<char *>(&CustomT), sizeof(CustomT));
        File.read(reinterpret_cast<char *>(&Color), sizeof(Color));
        File.read(reinterpret_cast<char *>(&Br), sizeof(Br));
    }
    // sets "origin" and "color" when loading with trenchbroom
    void SetVar(std::string Var,std::string Val) override{
        if(Var == "color"){
            TextSplit cf;
            cf.SetDivider(' ');
            cf.SetStr(Val);
            Color.X = stof(cf.GetText(0));
            Color.Y = stof(cf.GetText(1));
            Color.Z = stof(cf.GetText(2));
            Br = 1;
        }
        if(Var == "origin"){
            TextSplit cf;
            cf.SetDivider(' ');
            cf.SetStr(Val);
            Pos.X = stof(cf.GetText(0))*Engine_Map_Scale;
            Pos.Y = stof(cf.GetText(2))*Engine_Map_Scale;
            Pos.Z = stof(cf.GetText(1))*Engine_Map_Scale;
            Br = 1;
        }
    }

};


class LightFlood: public Ent{

    //Vec3 Color = {0.8,1,1};
    Vec3 Color = {int(rand()%1000)/1000.0f,int(rand()%1000)/1000.0f,int(rand()%1000)/1000.0f};
    float Br = 2;
    Vec3 LSize = {10000,-10000,10000};
    Vec3 Dir = {0.140,0,0.263};
    bool baked = false;
    GLuint DepthTx[3] = {0,0,0};

    std::string GetDebugName() override {
        return "LightFlood";
    }
    void CreateVarWindow(int cId,Vec2I W) override {
        ImGui::Begin((GetDebugName()+"##"+std::to_string(cId)).c_str());
        ImGui::SetWindowPos(ImVec2(0,W.Y-200));
        ImGui::SetWindowSize(ImVec2(200,200));
        ImGui::Text("light entity");
        ImGui::ColorEdit3("Light Color",&Color.X);
        ImGui::SliderFloat("light Brightness",&Br,0,40);
        ImGui::SliderFloat("DirX",&Dir.X,-1,1);
        ImGui::SliderFloat("DirZ",&Dir.Z,-1,1);

        ImGui::SliderFloat("SizeX",&LSize.X,0,5000);
        ImGui::SliderFloat("SizeZ",&LSize.Z,0,5000);
        ImGui::End();
    }
    GLuint Sh;
    float Think(float TPS) override{
        Pos = {0,6000,0};
        if(!baked){
            baked = true;
            Sh = OpenGlCreateShaderProgram("shaders/Light.vert.glsl","shaders/Light.frag.glsl");
            //DepthTx =BakeFloodLight(Pos,LSize,Dir,Sh,{float((*Display).X),float((*Display).Y)},*Ents);
            InitFloodLight(DepthTx[0],DepthTx[1],DepthTx[2]);
        }else{
            UpdateFloodLight(Pos,LSize,Dir,Sh,{float((*Display).X),float((*Display).Y)},*Ents,DepthTx[0],DepthTx[1],DepthTx[2]);
        }


        return 0;
    }

    void PreRender() override{
        if(baked) {
            AddFloodLight(LightsPtr, Pos, {Color.X * Br, Color.Y * Br, Color.Z * Br}, LSize, Dir, DepthTx[0]);
        }
    }

    void Render3D() override{
        glLineWidth(2);
        glUseProgram(NULL);
        glColor3ub(255,255,255);
        glBegin(GL_LINES);

        glVertex3f(Pos.X-LSize.X,Pos.Y,Pos.Z-LSize.Z);
        glVertex3f(Pos.X+LSize.X,Pos.Y,Pos.Z-LSize.Z);

        glVertex3f(Pos.X+LSize.X,Pos.Y,Pos.Z-LSize.Z);
        glVertex3f(Pos.X+LSize.X,Pos.Y,Pos.Z+LSize.Z);

        glVertex3f(Pos.X+LSize.X,Pos.Y,Pos.Z+LSize.Z);
        glVertex3f(Pos.X-LSize.X,Pos.Y,Pos.Z+LSize.Z);

        glVertex3f(Pos.X-LSize.X,Pos.Y,Pos.Z+LSize.Z);
        glVertex3f(Pos.X-LSize.X,Pos.Y,Pos.Z-LSize.Z);


        glVertex3f(Pos.X-LSize.X,Pos.Y,Pos.Z-LSize.Z);
        glVertex3f(Pos.X-LSize.X+(Dir.X*LSize.Y),Pos.Y+LSize.Y,Pos.Z-LSize.Z+(Dir.Z*LSize.Y));

        glVertex3f(Pos.X+LSize.X,Pos.Y,Pos.Z-LSize.Z);
        glVertex3f(Pos.X+LSize.X+(Dir.X*LSize.Y),Pos.Y+LSize.Y,Pos.Z-LSize.Z+(Dir.Z*LSize.Y));

        glVertex3f(Pos.X-LSize.X,Pos.Y,Pos.Z+LSize.Z);
        glVertex3f(Pos.X-LSize.X+(Dir.X*LSize.Y),Pos.Y+LSize.Y,Pos.Z+LSize.Z+(Dir.Z*LSize.Y));

        glVertex3f(Pos.X+LSize.X,Pos.Y,Pos.Z+LSize.Z);
        glVertex3f(Pos.X+LSize.X+(Dir.X*LSize.Y),Pos.Y+LSize.Y,Pos.Z+LSize.Z+(Dir.Z*LSize.Y));

        glEnd();
        glLineWidth(1);
    }
    void Render2D() override{
    }


};