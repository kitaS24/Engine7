//
// Created by kitaS24 on 18.08.2025.
//

// Copyright (c) 2025 kitaS24


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
#include <OpenAl/al.h>
#include <OpenAl/alc.h>
#include "structs.h"
#include "math.cpp"


//subsys (level 0)
#include "KeyMap.cpp"
#include "iniRead.cpp"
#include "Mouse.cpp"
//
#include "game/EntManager.h"
//subsys (level 1)
#include "CreateBrush.cpp"
#include "BrushTransform.cpp"
#include "Collision.cpp"
#include "Raycast.cpp"
#include "Light.cpp"
#include "Particle.cpp"
#include "TextFunctions.cpp"
#include "TextureLoad.cpp"
#include "AL_Setup.cpp"
#include "SoundEngine.cpp"
#include "EntName.cpp"


#include "GameSubsys.cpp"

//classes

#include "GameEnt.cpp"

#include "EntManager.cpp"
//subsys (level 2)
#include "save.cpp"
//import
#include "TrenchBroomImport.cpp"
#include "Vars.cpp"
//
#include "StartEntCreate.cpp"


class Engine{
private:
    IniRead Ini;
    EngineMouse Mouse;

    float T = 0;
    float FPS = 0;
    float LastFrameT = 0;
    float DebugTimeScale = 1;
    Vec2I WindowSize = {0,0};
    bool Map1stFrame = true;

    bool DebugGui = true;

    void EngineGlSetup(std::string Title){
        OpenGlInit(true);

        //creating window with W 800 and H 600
        glfwWindowHint(GLFW_DEPTH_BITS, 24);
        if(!CreateGlWindow(D.window,800,600,Title.c_str())){
            exit(-1);
        }
        //loading textures/ Missing Texture load
        LoadMaterials(Materials,"textures/textures.ini");
        Materials[0].Texture = LoadBmpTexture("textures/MissingTx.bmp",false,false);
        Mouse.SetupMouseCallBack(D.window,&Mouse);
        Mouse.SetSens(0.0625);
    }
    void EngineImGuiSetup(){
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        ImGui_ImplGlfw_InitForOpenGL(D.window,true);
        ImGui_ImplOpenGL3_Init();
        ImGui::StyleColorsDark();
    }
    void EngineQuickSaveLoad(){
        //if F6 or F9 for the fist frame ,then load or save
        if(glfwGetKey(D.window,Engine_Key_Save) ||glfwGetKey(D.window,Engine_Key_Load)){
            if(!SaveOrLoadKeyPress){
                if(glfwGetKey(D.window,Engine_Key_Save) ){
                    EngineSave(&LevelEnt,LevelBrushes,"saves/test1.gems");
                }
                if(glfwGetKey(D.window,Engine_Key_Load) ){
                    EngineLoad(&LevelEnt,LevelBrushes,"saves/test1.gems");
                }
            }
            SaveOrLoadKeyPress = true;
        }else{
            SaveOrLoadKeyPress = false;
        }
    }
    void EngineResetLights(){
        //resetting point lights
        for (int i = 0; i < Engine_Max_Lights; ++i) {
            Lights.Pos[i*3+0] = 0;
            Lights.Pos[i*3+1] = 0;
            Lights.Pos[i*3+2] = 0;
            Lights.Color[i*3+0] = 0;
            Lights.Color[i*3+1] = 0;
            Lights.Color[i*3+2] = 0;
            Lights.enabled[i] = false;
        }
        for (int i = 0; i < Engine_MaxSpotLights; ++i) {
            Lights.Dir[i*3+0] = 0;
            Lights.Dir[i*3+1] = 0;
            Lights.Dir[i*3+2] = 0;
            Lights.Data[i*3+0] = 0;
            Lights.Data[i*3+1] = 0;
            Lights.Data[i*3+2] = 0;
        }
        //resetting flood/sun light
        Lights.FloodPos = {0,0,0};
        Lights.FloodColor = {0,0,0};
        Lights.FloodDir = {0,0,0};
        Lights.FloodSize = {0,0,0};
        Lights.FloodEnabled = false;
    }

    void Engine1stFrame(){
        //call MapStart if the first frame of the map. (not quicksave)
        if(Map1stFrame){
            Map1stFrame = false;
            EntOnMapStartCall(LevelEnt);
        }
    }

    void LoadMap(){
        if(LevelTransition.LoadMap){
            EngineLoad(&LevelEnt,LevelBrushes,LevelTransition.MapName);
            Map1stFrame = LevelTransition.IsNewMap;
            LevelTransition.LoadMap = false;
            LevelTransition.IsNewMap = false;
        }
    }

public:

    void SetSwapInterval(int Swap){
        glfwSwapInterval(Swap);
    }

    void Setup(std::string Title){
        //engine setup, gl, window, keybinds, OpenAL setup
        EngineGlSetup(Title);
        EngineImGuiSetup();

        CreateEntsOnStartup();

        UserKeyBind.UpdateWindow(&D);
        UserKeyBind.SetupGlfwKeys();

        EngineAl.Setup();
    }
    bool Frame(){
        EngineAl.SetListener(Cam[0],Cam[2],true);
        glfwGetWindowSize(D.window,&D.X,&D.Y);

        EngineQuickSaveLoad();

        //frame start
        glfwGetWindowSize(D.window,&WindowSize.X,&WindowSize.Y);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if(DebugGui) {
            //debug entity list
            EntList(LevelEnt, DebugEntView, WindowSize, D);
        }




        //get FPS and time from start
        FPS = OpenGlGetFPS(LastFrameT)*DebugTimeScale;
        D.FPS = FPS;
        T = T+(1.0f/FPS);

        //debug window
        ImGui::Begin("DEBUG");
        ImGui::SliderFloat("TimeScale",&DebugTimeScale,0.5,100);
        ImGui::End();

        //map loading (if possible)
        LoadMap();
        Engine1stFrame();

        //entity tick,pointers
        EntUpdatePointers(LevelEnt,LevelBrushes,Materials,&Lights,&D,Cam,&UserKeyBind,&LevelTransition,&Mouse);
        EntUpdate(LevelEnt,T);
        EntThink(LevelEnt,FPS);

        EngineResetLights();

        //start 3D frame
        OpenGlErase(0.0f,0.7f,1.0f,1.0f,true,true);
        OpenGlBeginFrame3D(D.window,800,600,500000,true);

        //rotation/transformation test
        //RotateBrush(LevelBrushes[8],{0,T*10,0},{0,-400,0});
        //RotateBrush(LevelBrushes[9],{0,T*10,0},{0,-400,0});
        //RotateBrush(LevelBrushes[10],{0,T*10,0},{0,-400,0});

        //LevelBrushes[0].Transformation[0] = {T*10,0,0};

        //3D rendering
        EntPreRender(LevelEnt);
        EntRender3D(LevelEnt);

        //start 2D frame
        OpenGlBeginFrame2D(D.X,D.Y,-100,100);
        //render 2D frame
        EntRender2D(LevelEnt);

        if(!Mouse.GetInMenu()) {
            Mouse.CenterMouse();
        }
        Mouse.ResetInMenu();
        if(glfwGetKey(D.window,GLFW_KEY_ESCAPE)){
            Mouse.SetInMenu();
        }
        //killing ents
        KillAllRequestedObjs(LevelEnt);

        //render end

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(D.window);
        glfwPollEvents();

        return !glfwWindowShouldClose(D.window);
    }
    void Cleanup(){
        // that's cleanup
        EntCleanupCall(LevelEnt);
        EngineAl.Cleanup();
    }
    void CompileTrenchBroomMap(std::string ObjFile,std::string MapFile,std::string OutFile,std::string TexturesFile){
        //compile TrenchBroom map to savefile
        LoadTBMap(LevelBrushes,ObjFile,TexturesFile,LevelEnt);
        ImportEnts(MapFile,LevelEnt);
        EngineSave(&LevelEnt,LevelBrushes,OutFile);
    }


    void DebugMode(bool Val){
        // turns on/off debug GUI
        DebugGui = Val;
    }
};