//
// Created by kitaS24 on 18.08.2025.
//

class WorldRender : public Ent{

    unsigned int SceneLights = 0;

    //custom functions

    void RenderBrushSide(BrushSide &Side,Material *materials,GpuLights *L,unsigned int LN){

        if(Side.Material == 0){return;}

        glEnable(GL_TEXTURE_2D);
        if(!(*(materials+Side.Material)).Loaded){
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, (*(materials+0)).Texture);
            glUseProgram(NULL);
        }else {
            glActiveTexture(GL_TEXTURE0);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, (*(materials + Side.Material)).Texture);
            if((*(materials + Side.Material)).TxProperty) {
                glActiveTexture(GL_TEXTURE1);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, (*(materials + Side.Material)).TextureProperty);
            }
            glUseProgram((*(materials+Side.Material)).Shader);
            glUniform3fv(glGetUniformLocation((*(materials+Side.Material)).Shader, "LightPos"), LN,(*L).Pos);
            glUniform3fv(glGetUniformLocation((*(materials+Side.Material)).Shader, "LightCol"), LN,(*L).Color);
            glUniform1i(glGetUniformLocation((*(materials+Side.Material)).Shader, "LightN"), LN);
            glUniform1i(glGetUniformLocation((*(materials+Side.Material)).Shader, "Property"), (*(materials + Side.Material)).TxProperty);
            glUniform1i(glGetUniformLocation((*(materials+Side.Material)).Shader, "PropTex"), 1);
            glUniform3f(glGetUniformLocation((*(materials+Side.Material)).Shader, "CamPos"), (*CamPos).X,(*CamPos).Y,(*CamPos).Z);

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
        glActiveTexture(GL_TEXTURE1);
        glDisable(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);

    }
    void RenderBrush(Brush &Br,Material *materials,GpuLights *L,unsigned int LN){
        if(!Br.Active){return;}
        for (int i = 0; i < Br.Planes; ++i) {
            if(Br.BrushPlane[i].Used) {
                RenderBrushSide(Br.BrushPlane[i],materials,L,LN);
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
        //ImGui::Text("No Variables yet");
        ImGui::Text(("Lights:"+std::to_string(SceneLights)).c_str());
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
        //std::cout << LightsN<<"\n";

        for (int i = 0; i < Engine_Max_Brushes; ++i) {
            RenderBrush(*(Brushes+i),Materials,LightsPtr,LightsN);
        }
    }
};