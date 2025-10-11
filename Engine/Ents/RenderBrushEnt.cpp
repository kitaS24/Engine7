//
// Created by kitaS24 on 18.08.2025.
//

// Copyright (c) 2025 kitaS24

class WorldRender : public Ent{

    unsigned int SceneLights = 0;
    unsigned int FloodSceneLights = 0;

    //custom functions

    void RenderBrushSide(BrushSide &Side,Material *materials,GpuLights *L,unsigned int LN){

        if(Side.Material == 0){return;}

        glEnable(GL_TEXTURE_2D);
        if((!(*(materials+Side.Material)).Loaded)){
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, (*(materials+0)).Texture);
            glUseProgram(NULL);
        }else {
            glActiveTexture(GL_TEXTURE0);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, (*(materials + Side.Material)).Texture);
            //glBindTexture(GL_TEXTURE_2D,(*L).Depth[0]);
            if((*(materials + Side.Material)).TxProperty) {
                glActiveTexture(GL_TEXTURE1);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, (*(materials + Side.Material)).TextureProperty);
                glActiveTexture(GL_TEXTURE2);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, (*L).Depth);
            }
            glUseProgram((*(materials+Side.Material)).Shader);
            glUniform3fv(glGetUniformLocation((*(materials+Side.Material)).Shader, "LightPos"), LN,(*L).Pos);
            glUniform3fv(glGetUniformLocation((*(materials+Side.Material)).Shader, "LightCol"), LN,(*L).Color);

            glUniform3fv(glGetUniformLocation((*(materials+Side.Material)).Shader, "LightDir"), ClampInt(LN,0,Engine_MaxSpotLights-1),(*L).Dir);
            glUniform3fv(glGetUniformLocation((*(materials+Side.Material)).Shader, "LightDt"), ClampInt(LN,0,Engine_MaxSpotLights-1),(*L).Data);
            glUniform1i(glGetUniformLocation((*(materials+Side.Material)).Shader, "LightN"), LN);

            glUniform3f(glGetUniformLocation((*(materials+Side.Material)).Shader, "FloodPos"),(*L).FloodPos.X,(*L).FloodPos.Y,(*L).FloodPos.Z);
            glUniform3f(glGetUniformLocation((*(materials+Side.Material)).Shader, "FloodCol"),(*L).FloodColor.X,(*L).FloodColor.Y,(*L).FloodColor.Z);
            glUniform3f(glGetUniformLocation((*(materials+Side.Material)).Shader, "FloodSize"),(*L).FloodSize.X,(*L).FloodSize.Y,(*L).FloodSize.Z);
            glUniform3f(glGetUniformLocation((*(materials+Side.Material)).Shader, "FloodDir"),(*L).FloodDir.X,(*L).FloodDir.Y,(*L).FloodDir.Z);
            glUniform1i(glGetUniformLocation((*(materials+Side.Material)).Shader, "FloodN"), (*L).FloodEnabled);

            glUniform1i(glGetUniformLocation((*(materials+Side.Material)).Shader, "Property"), (*(materials + Side.Material)).TxProperty);
            glUniform1i(glGetUniformLocation((*(materials+Side.Material)).Shader, "PropTex"), 1);
            glUniform1i(glGetUniformLocation((*(materials+Side.Material)).Shader, "FloodD"), 2);
            glUniform3f(glGetUniformLocation((*(materials+Side.Material)).Shader, "CamPos"), (*(CamPos)).X,(*(CamPos)).Y,(*(CamPos)).Z);
            if((*(materials + Side.Material)).Metal) {
                glUniform3f(glGetUniformLocation((*(materials + Side.Material)).Shader, "SpecColor"),
                            (*(materials + Side.Material)).SpecColor.X, (*(materials + Side.Material)).SpecColor.Y,
                            (*(materials + Side.Material)).SpecColor.Z);
            }else{
                glUniform3f(glGetUniformLocation((*(materials + Side.Material)).Shader, "SpecColor"),
                            (*(materials + Side.Material)).SpecColor.X*0.08, (*(materials + Side.Material)).SpecColor.Y*0.08,
                            (*(materials + Side.Material)).SpecColor.Z*0.08);
            }
        }

        glBegin(GL_TRIANGLES);
        glMultiTexCoord3f(GL_TEXTURE2,Side.Normal.X,Side.Normal.Y,Side.Normal.Z);
        for (int i = 0; i < Side.VertexN-2; ++i) {
            glMultiTexCoord2f(GL_TEXTURE0,Side.Uvs[0].X,Side.Uvs[0].Y);
            glMultiTexCoord3f(GL_TEXTURE1,Side.Vertex[0].X,Side.Vertex[0].Y,Side.Vertex[0].Z);
            glVertex3f(Side.Vertex[0].X,Side.Vertex[0].Y,Side.Vertex[0].Z);
            glMultiTexCoord2f(GL_TEXTURE0,Side.Uvs[i+1].X,Side.Uvs[i+1].Y);
            glMultiTexCoord3f(GL_TEXTURE1,Side.Vertex[i+1].X,Side.Vertex[i+1].Y,Side.Vertex[i+1].Z);
            glVertex3f(Side.Vertex[i+1].X,Side.Vertex[i+1].Y,Side.Vertex[i+1].Z);
            glMultiTexCoord2f(GL_TEXTURE0,Side.Uvs[i+2].X,Side.Uvs[i+2].Y);
            glMultiTexCoord3f(GL_TEXTURE1,Side.Vertex[i+2].X,Side.Vertex[i+2].Y,Side.Vertex[i+2].Z);
            glVertex3f(Side.Vertex[i+2].X,Side.Vertex[i+2].Y,Side.Vertex[i+2].Z);
        }
        glEnd();
        glActiveTexture(GL_TEXTURE2);
        glDisable(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE1);
        glDisable(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);

    }
    void ShadowRenderBrushSide(BrushSide &Side,GLuint Shader,Vec3 LightPos,Vec3 LightSize,Vec3 LightDir){

        if(Side.Material == 0){return;}
        glUseProgram(Shader);
        glUniform3f(glGetUniformLocation(Shader, "FloodPos"), LightPos.X, LightPos.Y, LightPos.Z);
        glUniform3f(glGetUniformLocation(Shader, "FloodSize"), LightSize.X, LightSize.Y, LightSize.Z);
        glUniform3f(glGetUniformLocation(Shader, "FloodDir"), LightDir.X, LightDir.Y, LightDir.Z);

        glBegin(GL_TRIANGLES);
        glMultiTexCoord3f(GL_TEXTURE2,Side.Normal.X,Side.Normal.Y,Side.Normal.Z);
        for (int i = 0; i < Side.VertexN-2; ++i) {
            glMultiTexCoord2f(GL_TEXTURE0,Side.Uvs[0].X,Side.Uvs[0].Y);
            glMultiTexCoord3f(GL_TEXTURE1,Side.Vertex[0].X,Side.Vertex[0].Y,Side.Vertex[0].Z);
            glVertex3f(Side.Vertex[0].X,Side.Vertex[0].Y,Side.Vertex[0].Z);
            glMultiTexCoord2f(GL_TEXTURE0,Side.Uvs[i+1].X,Side.Uvs[i+1].Y);
            glMultiTexCoord3f(GL_TEXTURE1,Side.Vertex[i+1].X,Side.Vertex[i+1].Y,Side.Vertex[i+1].Z);
            glVertex3f(Side.Vertex[i+1].X,Side.Vertex[i+1].Y,Side.Vertex[i+1].Z);
            glMultiTexCoord2f(GL_TEXTURE0,Side.Uvs[i+2].X,Side.Uvs[i+2].Y);
            glMultiTexCoord3f(GL_TEXTURE1,Side.Vertex[i+2].X,Side.Vertex[i+2].Y,Side.Vertex[i+2].Z);
            glVertex3f(Side.Vertex[i+2].X,Side.Vertex[i+2].Y,Side.Vertex[i+2].Z);
        }
        glEnd();
        glActiveTexture(GL_TEXTURE2);
        glDisable(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE1);
        glDisable(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);

    }
    void RenderBrush(Brush &Br,Material *materials,GpuLights *L,unsigned int LN){
        if(!Br.Active){return;}
        BrushSide BS = {};
        for (int i = 0; i < Br.Planes; ++i) {
            if(Br.BrushPlane[i].Used) {
                BS = RenderSideRotate(Br.BrushPlane[i],Br.Transformation,Br.RotMatrix);
                RenderBrushSide(BS,materials,L,LN);
            }
        }
    }
    void ShadowRenderBrush(Brush &Br,GLuint Shader,Vec3 LightPos,Vec3 LightSize,Vec3 LightDir){
        if(!Br.Active){return;}
        BrushSide BS = {};
        for (int i = 0; i < Br.Planes; ++i) {
            if(Br.BrushPlane[i].Used) {
                BS = RenderSideRotate(Br.BrushPlane[i],Br.Transformation,Br.RotMatrix);
                ShadowRenderBrushSide(BS,Shader,LightPos,LightSize,LightDir);
            }
        }
    }

    //events

    std::string GetDebugName() override {
        return "WorldRender";
    }
    void CreateVarWindow(int cId,Vec2I W) override {
        ImGui::Begin((GetDebugName()+"##"+std::to_string(cId)).c_str());
        ImGui::SetWindowPos(ImVec2(0,W.Y-200));
        ImGui::SetWindowSize(ImVec2(200,200));
        ImGui::Text(("Lights:"+std::to_string(SceneLights)).c_str());
        ImGui::Text(("FloodLights:"+std::to_string(FloodSceneLights)).c_str());
        ImGui::End();
    }
    void Render3D() override{

        unsigned int LightsN = 0;
        for (int i = 0; i < Engine_Max_Lights; ++i) {
            if(!(*LightsPtr).enabled[i]){
                LightsN = i;
                break;
            }
        }
        SceneLights = LightsN;
        if(LightsN >512){
            LightsN = 512;
        }


        FloodSceneLights = (*LightsPtr).FloodEnabled;


        for (int i = 0; i < Engine_Max_Brushes; ++i) {
            glColor3ub(255,255,255);
            RenderBrush(*(Brushes+i),Materials,LightsPtr,LightsN);
        }
    }

    void ShadowPass(Vec3 LightPos,Vec3 LightSize,Vec3 LightDir,GLuint Shader) override{
        for (int i = 0; i < Engine_Max_Brushes; ++i) {
            glColor3ub(255,255,255);
            ShadowRenderBrush(*(Brushes+i),Shader,LightPos,LightSize,LightDir);
        }
    }
};