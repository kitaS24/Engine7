//
// Created by kitaS24 on 18.08.2025.
//

#include "Core.h"
#include <vector>
#include <memory>

#include <iostream>

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ImGuiSetup.h"
#include "OpenGLRenderer.cpp"
#include "structs.h"
#include "math.cpp"
#include "EntManager.h"
#include "Vars.cpp"
//subsys
#include "CreateBrush.cpp"
#include "Light.cpp"
#include "Collision.cpp"
#include "Raycast.cpp"
#include "Particle.cpp"
//classes
#include "RenderBrushEnt.cpp"
#include "PlayerEnt.cpp"
#include "LightEnt.cpp"
#include "particleEnt.cpp"
#include "EntManager.cpp"



void Engine(){
    float T = 0;
    float FPS = 0;
    float LastFrameT = 0;
    Vec2I WindowSize = {0,0};
        OpenGlInit(true);

        //creating window with W 800 and H 600
        if(!CreateGlWindow(D.window,800,600,"Test")){
            exit(-1);
        }
    Materials[0].Texture = LoadBmpTexture("MissingTx.bmp",false,false);
        Materials[1].Texture = LoadBmpTexture("portal2.bmp",false,false);
        Materials[1].Shader = OpenGlCreateShaderProgram("shaders/base.vert.glsl","shaders/base.frag.glsl");
    Materials[1].Loaded = true;
    Materials[2].Texture = LoadBmpTexture("portal2Metal.bmp",false,false);
    Materials[2].TextureProperty = LoadBmpTexture("portal2MetalDt.bmp",false,false);
    Materials[2].Shader = OpenGlCreateShaderProgram("shaders/base.vert.glsl","shaders/base.frag.glsl");
    Materials[2].Loaded = true;
    Materials[2].TxProperty = true;
    Materials[3].Texture = LoadBmpTexture("portal2Metal.bmp",false,false);
    Materials[3].Shader = OpenGlCreateShaderProgram("shaders/base.vert.glsl","shaders/base.frag.glsl");
    Materials[3].Loaded = true;
    Materials[4].Texture = LoadBmpTexture("plastic1.bmp",false,false);
    Materials[4].TextureProperty = LoadBmpTexture("plastic1Dt.bmp",false,false);
    Materials[4].Shader = OpenGlCreateShaderProgram("shaders/base.vert.glsl","shaders/base.frag.glsl");
    Materials[4].Loaded = true;
    Materials[4].TxProperty = true;
    Materials[5].Texture = LoadBmpTexture("test.bmp",false,false);
    Materials[5].TextureProperty = LoadBmpTexture("testDt.bmp",false,false);
    Materials[5].Shader = OpenGlCreateShaderProgram("shaders/base.vert.glsl","shaders/base.frag.glsl");
    Materials[5].Loaded = true;
    Materials[5].TxProperty = true;
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui_ImplGlfw_InitForOpenGL(D.window,true);
    ImGui_ImplOpenGL3_Init();
        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();
    //SetCustomImStyle();

    LevelEnt.push_back(std::make_unique<Ent>());
    LevelEnt.push_back(std::make_unique<Ent>());
    LevelEnt.push_back(std::make_unique<Ent>());
    LevelEnt.push_back(std::make_unique<WorldRender>());
    LevelEnt.push_back(std::make_unique<Particle>());
    //LevelEnt.push_back(std::make_unique<Light>());
    //LevelEnt.push_back(std::make_unique<Light>());
    //LevelEnt.push_back(std::make_unique<Light>());
    for (int i = 0; i < 10; ++i) {
        LevelEnt.push_back(std::make_unique<Light>());
    }

    LevelEnt.push_back(std::make_unique<Player>());

    LevelBrushes[0].BrushPlane[0].Vertex[0] = {1000,-1000,1000};
    LevelBrushes[0].BrushPlane[0].Vertex[1] = {-1000,-1000,1000};
    LevelBrushes[0].BrushPlane[0].Vertex[2] = {-1000,-1000,-1000};
    LevelBrushes[0].BrushPlane[0].Vertex[3] = {1000,-1000,-1000};
    LevelBrushes[0].BrushPlane[0].Used = true;
    LevelBrushes[0].BrushPlane[0].VertexN = 4;
    LevelBrushes[0].BrushPlane[1].Vertex[0] = {1000,1000,1000};
    LevelBrushes[0].BrushPlane[1].Vertex[1] = {-1000,1000,1000};
    LevelBrushes[0].BrushPlane[1].Vertex[2] = {-1000,1000,-1000};
    LevelBrushes[0].BrushPlane[1].Vertex[3] = {1000,1000,-1000};
    LevelBrushes[0].BrushPlane[1].Used = true;
    LevelBrushes[0].BrushPlane[1].VertexN = 4;
    LevelBrushes[0].BrushPlane[2].Vertex[0] = {-1000,1000,1000};
    LevelBrushes[0].BrushPlane[2].Vertex[1] = {-1000,-1000,1000};
    LevelBrushes[0].BrushPlane[2].Vertex[2] = {-1000,-1000,-1000};
    LevelBrushes[0].BrushPlane[2].Vertex[3] = {-1000,1000,-1000};
    LevelBrushes[0].BrushPlane[2].Used = true;
    LevelBrushes[0].BrushPlane[2].VertexN = 4;
    LevelBrushes[0].BrushPlane[3].Vertex[0] = {1000,1000,1000};
    LevelBrushes[0].BrushPlane[3].Vertex[1] = {1000,-1000,1000};
    LevelBrushes[0].BrushPlane[3].Vertex[2] = {1000,-1000,-1000};
    LevelBrushes[0].BrushPlane[3].Vertex[3] = {1000,1000,-1000};
    LevelBrushes[0].BrushPlane[3].Used = true;
    LevelBrushes[0].BrushPlane[3].VertexN = 4;
    LevelBrushes[0].BrushPlane[4].Vertex[0] = {1000,1000,-1000};
    LevelBrushes[0].BrushPlane[4].Vertex[1] = {-1000,1000,-1000};
    LevelBrushes[0].BrushPlane[4].Vertex[2] = {-1000,-1000,-1000};
    LevelBrushes[0].BrushPlane[4].Vertex[3] = {1000,-1000,-1000};
    LevelBrushes[0].BrushPlane[4].Used = true;
    LevelBrushes[0].BrushPlane[4].VertexN = 4;
    LevelBrushes[0].BrushPlane[5].Vertex[0] = {1000,1000,1000};
    LevelBrushes[0].BrushPlane[5].Vertex[1] = {-1000,1000,1000};
    LevelBrushes[0].BrushPlane[5].Vertex[2] = {-1000,-1000,1000};
    LevelBrushes[0].BrushPlane[5].Vertex[3] = {1000,-1000,1000};
    LevelBrushes[0].BrushPlane[5].Used = true;
    LevelBrushes[0].BrushPlane[5].VertexN = 4;
    LevelBrushes[0].Active = true;
    LevelBrushes[0].Planes = 6;

    LevelBrushes[0].BrushPlane[0].Normal = {0,-1,0};
    LevelBrushes[0].BrushPlane[1].Normal = {0,1,0};
    LevelBrushes[0].BrushPlane[2].Normal = {-1,0,0};
    LevelBrushes[0].BrushPlane[3].Normal = {1,0,0};
    LevelBrushes[0].BrushPlane[4].Normal = {0,0,-1};
    LevelBrushes[0].BrushPlane[5].Normal = {0,0,1};

    LevelBrushes[0].BrushPlane[0].CollisionPos = {0,-1000,0};
    LevelBrushes[0].BrushPlane[1].CollisionPos = {0,1000,0};
    LevelBrushes[0].BrushPlane[2].CollisionPos = {-1000,0,0};
    LevelBrushes[0].BrushPlane[3].CollisionPos = {1000,0,0};
    LevelBrushes[0].BrushPlane[4].CollisionPos = {0,0,-1000};
    LevelBrushes[0].BrushPlane[5].CollisionPos = {0,0,1000};

    for (int i = 0; i < 6; ++i) {
        LevelBrushes[0].BrushPlane[i].Uvs[0] = {1,1};
        LevelBrushes[0].BrushPlane[i].Uvs[1] = {0,1};
        LevelBrushes[0].BrushPlane[i].Uvs[2] = {0,0};
        LevelBrushes[0].BrushPlane[i].Uvs[3] = {1,0};
        LevelBrushes[0].BrushPlane[i].Material = 2;
    }
    CreateBrushBoundingBox(LevelBrushes[0]);

    glfwSwapInterval(1);

        while(!glfwWindowShouldClose(D.window))
        {
            glfwGetWindowSize(D.window,&WindowSize.X,&WindowSize.Y);
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            //ImGui::Text("Hello, World!");
            EntList(LevelEnt,DebugEntView,WindowSize);

            // clear and start in 3D mode
            OpenGlErase(0.0f,0.7f,1.0f,1.0f,true,true);
            OpenGlBeginFrame3D(D.window,800,600,500000,true);

            //get FPS and time from start
            FPS = OpenGlGetFPS(LastFrameT);
            T = T+(1.0f/FPS);

            EntUpdatePointers(LevelEnt,LevelBrushes,Materials,&Lights,&D,Cam);
            EntUpdate(LevelEnt,T);
            EntThink(LevelEnt,FPS);

            //rotate and transform triangle
            //glTranslatef(0,0,40);
            //Rotate3D(-T*2.0f,-T*9.0f,-T*3.0f);
            for (int i = 0; i < Engine_Max_Lights; ++i) {
                Lights.Pos[i*3+0] = 0;
                Lights.Pos[i*3+1] = 0;
                Lights.Pos[i*3+2] = 0;
                Lights.Color[i*3+0] = 0;
                Lights.Color[i*3+1] = 0;
                Lights.Color[i*3+2] = 0;
                Lights.enabled[i] = false;
            }

            for (int i = 0; i < 6; ++i) {
                //LevelBrushes[0].BrushPlane[i].Material = 2+(int(T*0.5)%2);
            }

            //rendering triangle with color (255,255,255) or with different colors for each vertex
            EntPreRender(LevelEnt);
            EntRender3D(LevelEnt);
            KillAllRequestedObjs(LevelEnt);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            //ending rendering
            glfwSwapBuffers(D.window);
            glfwPollEvents();
        }
        return;

}