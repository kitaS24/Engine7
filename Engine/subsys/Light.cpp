//
// Created by kitaS24 on 19.08.2025.
//

void AddLight(GpuLights *L,Vec3 Pos,Vec3 Color){
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
    if(!(*L).FloodEnabled) {
        (*L).FloodPos= Pos;
        (*L).FloodColor= Color;

        (*L).FloodSize= Size;
        (*L).FloodDir= Dir;

        (*L).Depth= DT;
        (*L).FloodEnabled= true;
    }
}

void LightCalcRenderBrushSide(BrushSide &Side,GLuint Shader,Vec3 LightPos,Vec3 LightSize,Vec3 LightDir){

    if(Side.Material == 0){return;}
    glUseProgram(Shader);
    //glUseProgram(NULL);
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
void LightCalcRenderBrush(Brush &Br,GLuint Shader,Vec3 LightPos,Vec3 LightSize,Vec3 LightDir){
    if(!Br.Active){return;}
    for (int i = 0; i < Br.Planes; ++i) {
        if(Br.BrushPlane[i].Used) {
            LightCalcRenderBrushSide(Br.BrushPlane[i],Shader,LightPos,LightSize,LightDir);
        }
    }
}


void InitFloodLight(GLuint &tx,GLuint &fbo,GLuint &rbo){
    //float Data[512][512] = {};

    /*
    float * Data;
    int Size = 1024;
    Data = new float [Size*Size];

    Vec3 TexPos = {};
    Vec3 CollisionSize = {};

    int compilation[8] = {128,64,32,16,8,4,4,1};
    int compilationYS[8] = {5000,2000,1000,750,500,350,250,100};

    int LodI = Lod;
    if(Lod >8){LodI = 8;}
    if(Lod <0){LodI = 0;}

    for (int i = 0; i < Size*Size; ++i) {
        Data[i] = 0;
    }

    for (int Step = 0; Step < LodI; ++Step) {
        std::cout << "Step:"<<Step;

        CollisionSize = Vec3Divide({LightSize.X,float(compilationYS[Step]),LightSize.Z},{float(Size)/float(compilation[Step])/2.0f,1/2.0f, float(Size)/float(compilation[Step])/2.0f});
        //std::cout << "X:"<<CollisionSize.X<<"|Z:"<<CollisionSize.Z<<"\n";
        for (int x = 0; x < Size; x=x+compilation[Step]) {
            for (int z = 0; z < Size; z=z+compilation[Step]) {

                TexPos = {(float(x+(float(compilation[Step])/2))/float(Size))-0.5f,0,(float(z+(float(compilation[Step])/2))/float(Size))-0.5f};
                //std::cout << "X:"<<TexPos.X<<"|Z:"<<TexPos.Z<<"\n";
                TexPos =Vec3Add(Vec3Multiply(TexPos, LightSize),LightPos);
                if(Step == LodI-1){
                    *(Data + (z * Size) + x) = *(Data + (z * Size) + x) +
                                               WorldRaycast(Vec3Add(TexPos,{LightDir.X *-Data[(z *Size) +x],
                                                                            -Data[(z *Size) +x],LightDir.Z *-Data[(z *Size) +x]}),

                                                            Vec3Add(TexPos,{LightDir.X * -250000,-250000,
                                                                            LightDir.Z * -250000}),

                                                            CollisionSize,
                                                            float(compilationYS[Step]),Brushes)+(compilationYS[Step]*2.0f);
                }else {
                    *(Data + (z * Size) + x) = *(Data + (z * Size) + x) +
                            WorldRaycast(Vec3Add(TexPos,{LightDir.X *-Data[(z *Size) +x],
                                                         -Data[(z *Size) +x],LightDir.Z *-Data[(z *Size) +x]}),

                                         Vec3Add(TexPos,{LightDir.X * -250000,-250000,
                                                         LightDir.Z * -250000}),

                                         Vec3Divide({LightSize.X,
                                         float(compilationYS[Step]),LightSize.Z},
                                         {Size /float(compilation[Step]),1, Size /float(compilation[Step])}),
                                         float(compilationYS[Step]),Brushes)-(compilationYS[Step] * 1.75);
                }
                if(Data[(z*Size)+x] <0){Data[(z*Size)+x] = 0;}

                for (int u = 0; u < compilation[Step]; ++u) {
                    for (int v = 0; v < compilation[Step]; ++v) {
                        Data[((z+u)*Size)+(x+v)]= Data[(z*Size)+x];
                    }
                }

            }

        }
        std::cout << "  done!\n";
    }


    GLuint tx = CreateDepthTx(Size,Size,Data,false);
    delete[] Data;
    return tx;
*/


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
    //glBindFramebuffer(GL_FRAMEBUFFER, fbo);


    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tx, 0);
    GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, drawBuffers);
    //if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    //    std::cout << "FBO not complete!" << std::endl;
    //}

    //call
    //OpenGlBeginFrame2D(Size,Size,1,100000);

    /*
    OpenGlErase(0.0f,0.0f,0.0f,1.0f,true,true);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND); // Enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set blend
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-LightSize.X/1, LightSize.X/1, LightSize.Z/1, -LightSize.Z/1, -1, -100000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glScalef(1,-1,1);
     */
    //OpenGlBeginFrame2D(5000,5000,-1,10000);

    //glRotatef(-90,1,0,0);
    //glRotatef(Rot.Y,0,1,0);

    //Rotate3D(P.Rot.X,P.Rot.Y,P.Rot.Z);
    //glTranslatef(-LightPos.X,-LightPos.Y,-LightPos.Z);
    /*
    for (int i = 0; i < Engine_Max_Brushes; ++i) {
        glColor3ub(255,255,255);
        LightCalcRenderBrush(*(Brushes+i),Shader,LightPos,LightSize,LightDir);
    }*/
    /*
        for (int i = 0; i < Ent.size(); i++) {
            if (Ent[i]) {
                Ent[i]->ShadowPass(LightPos,LightSize,LightDir,Shader);
            }
        }*/


    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //glDeleteFramebuffers(1,&fbo);
    //glfwGetWindowSize()
    //glViewport(0, 0, WindowSize.X, WindowSize.Y);
    //OpenGlErase(0.0f,0.0f,0.0f,1.0f,true,true);
    //return 0;

    //return tx;
}



void UpdateFloodLight(Vec3 LightPos,Vec3 LightSize,Vec3 LightDir,GLuint Shader,Vec2 WindowSize,std::vector<std::unique_ptr<Ent>> &Ent,GLuint &tx,GLuint &fbo,GLuint &rbo){


    int Size = 2048*2;
    glViewport(0, 0, Size, Size);


    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tx, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, Size, Size);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "FBO not complete!" << std::endl;
    }

    //call
    //OpenGlBeginFrame2D(Size,Size,1,100000);

    OpenGlErase(0.0f,0.0f,0.0f,1.0f,true,true);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-LightSize.X/1, LightSize.X/1, LightSize.Z/1, -LightSize.Z/1, 1, 100000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glScalef(1,1,1);
    //OpenGlBeginFrame2D(5000,5000,-1,10000);

    glRotatef(90,1,0,0);
    //glRotatef(Rot.Y,0,1,0);

    //Rotate3D(P.Rot.X,P.Rot.Y,P.Rot.Z);
    glTranslatef(-LightPos.X,-LightPos.Y,-LightPos.Z);
    /*
    for (int i = 0; i < Engine_Max_Brushes; ++i) {
        glColor3ub(255,255,255);
        LightCalcRenderBrush(*(Brushes+i),Shader,LightPos,LightSize,LightDir);
    }*/
    for (int i = 0; i < Ent.size(); i++) {
        if (Ent[i]) {
            Ent[i]->ShadowPass(LightPos,LightSize,LightDir,Shader);
        }
    }


    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //glDeleteFramebuffers(1,&fbo);//
    //glDeleteRenderbuffers(1, &rbo);
    //glfwGetWindowSize()
    glViewport(0, 0, WindowSize.X, WindowSize.Y);
    OpenGlErase(0.0f,0.0f,0.0f,1.0f,true,true);
    //return 0;
}