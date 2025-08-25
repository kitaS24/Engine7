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


class LightFlood: public Ent{

    //Vec3 Color = {0.8,1,1};
    Vec3 Color = {int(rand()%1000)/1000.0f,int(rand()%1000)/1000.0f,int(rand()%1000)/1000.0f};
    float Br = 0.5;
    Vec3 LSize = {10000,-10000,10000};
    Vec3 Dir = {0.140,0,0.263};
    bool baked = false;
    GLuint DepthTx = 0;

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

        ImGui::SliderFloat("SizeX",&LSize.X,0,1000);
        ImGui::SliderFloat("SizeZ",&LSize.Z,0,1000);
        ImGui::End();
    }
    GLuint Sh;
    void PreRender() override{
        Pos = {0,6000,0};
        //Vec3 Rot = {0,3500,0};
        if(!baked){
            baked = true;
            Sh = OpenGlCreateShaderProgram("shaders/Light.vert.glsl","shaders/Light.frag.glsl");
            DepthTx =BakeFloodLight(Pos,LSize,Dir,Brushes,8,Sh,{float((*Display).X),float((*Display).Y)});

        }

        AddFloodLight(LightsPtr, Pos,{Color.X*Br,Color.Y*Br,Color.Z*Br},LSize,Dir,DepthTx);
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
        /*
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, DepthTx);
        glUseProgram(NULL);
        glColor3f(0.1f,1,1);
        glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(0,0,1);
        glTexCoord2f(1,0);
        glVertex3f(600,0,1);
        glTexCoord2f(1,1);
        glVertex3f(600,600,1);
        glTexCoord2f(0,1);
        glVertex3f(0,600,1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
         */
    }

    /*
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
    }*/

};