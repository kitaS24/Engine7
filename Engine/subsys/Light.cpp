//
// Created by kitaS24 on 19.08.2025.
//

void AddLight(GpuLights *L,Vec3 Pos,Vec3 Color){
    //adds light to the scene (needs to be added every frame)
    int Index = 0;
    for (int i = 0; i < Engine_Max_Lights; ++i) {
        if(!(*L).enabled[i]){
            Index = i;
            break;
        }
    }
    (*L).Pos[Index*3+0] = Pos.X;
    (*L).Pos[Index*3+1] = Pos.Y;
    (*L).Pos[Index*3+2] = Pos.Z;

    (*L).Color[Index*3+0] = Color.X;
    (*L).Color[Index*3+1] = Color.Y;
    (*L).Color[Index*3+2] = Color.Z;

    (*L).enabled[Index] = true;
}

void AddFloodLight(GpuLights *L,Vec3 Pos,Vec3 Color,Vec3 Size,Vec3 Dir,GLuint DT){
    //adds flood/sun light to the scene (needs to be added every frame)
    if(!(*L).FloodEnabled) {
        (*L).FloodPos= Pos;
        (*L).FloodColor= Color;

        (*L).FloodSize= Size;
        (*L).FloodDir= Dir;

        (*L).Depth= DT;
        (*L).FloodEnabled= true;
    }
}

// USELESS
void LightCalcRenderBrushSide(BrushSide &Side,GLuint Shader,Vec3 LightPos,Vec3 LightSize,Vec3 LightDir){

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
//USELESS
void LightCalcRenderBrush(Brush &Br,GLuint Shader,Vec3 LightPos,Vec3 LightSize,Vec3 LightDir){
    if(!Br.Active){return;}
    for (int i = 0; i < Br.Planes; ++i) {
        if(Br.BrushPlane[i].Used) {
            LightCalcRenderBrushSide(Br.BrushPlane[i],Shader,LightPos,LightSize,LightDir);
        }
    }
}

// creates flood light texture
void InitFloodLight(GLuint &tx,GLuint &fbo,GLuint &rbo){

    int Size = 2048*2;
    glViewport(0, 0, Size, Size);
    glGenTextures(1, &tx);
    glBindTexture(GL_TEXTURE_2D, tx);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, Size, Size, 0, GL_RED, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    glGenFramebuffers(1, &fbo);
    glGenRenderbuffers(1, &rbo);


    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tx, 0);
    GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, drawBuffers);
}


//updates floodlight
void UpdateFloodLight(Vec3 LightPos,Vec3 LightSize,Vec3 LightDir,GLuint Shader,Vec2 WindowSize,std::vector<std::unique_ptr<Ent>> &Ent,GLuint &tx,GLuint &fbo,GLuint &rbo){


    int Size = 2048*2;
    glViewport(0, 0, Size, Size);

    // sets a render tx
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tx, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, Size, Size);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "FBO not complete!" << std::endl;
    }

    //call

    OpenGlErase(0.0f,0.0f,0.0f,1.0f,true,true);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-LightSize.X/1, LightSize.X/1, LightSize.Z/1, -LightSize.Z/1, 1, 100000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(90,1,0,0);
    glTranslatef(-LightPos.X,-LightPos.Y,-LightPos.Z);

    //tries to make every entity render something
    for (int i = 0; i < Ent.size(); i++) {
        if (Ent[i]) {
            Ent[i]->ShadowPass(LightPos,LightSize,LightDir,Shader);
        }
    }

    //returns to default
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(0, 0, WindowSize.X, WindowSize.Y);
    OpenGlErase(0.0f,0.0f,0.0f,1.0f,true,true);

}