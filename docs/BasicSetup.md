# Basic Setup
this file explains basic setup for any project

this file contains filenames and basic code for them (referenced by README.md)

#### EntManager.h
```
//
// Created by kitaS24 on 18.08.2025.
//

// Copyright (c) 2025 kitaS24

#ifndef ENGINE7_ENTMANAGER_H
#define ENGINE7_ENTMANAGER_H

#include "structs.h"
#include "math.cpp"
#include "Mouse.cpp"
#include <string>
#include <vector>
#include <memory>

class Ent{
private:
    float ThinkTimer = 0;
    bool Kill = false;
protected:
    Brush *Brushes;
    Material *Materials;
    GpuLights *LightsPtr;
    Vec3 Pos;
    Vec3 Rot;
    Vec3 Vel;
    Vec3 Scale;
    float Time;
    DISPLAY *Display;
    Vec3 *CamPos;
    Vec3 *CamRot;
    Vec3 *CamRotVec;
    MapKey *UserKeyBind;
    std::vector<std::unique_ptr<Ent>> *Ents;
    MapTransition *Transition;
    EngineMouse *Mouse;
    Ent * Self;// pointer to itself
    std::string Name;// entity name

    float weight;//kg



    void ChangeMap(std::string Map,bool IsNewMap){
        (*Transition).MapName = Map;
        (*Transition).IsNewMap = IsNewMap;
        (*Transition).LoadMap = true;
    }
public:

    Vec3 BoundingBox[2];


    virtual std::string GetDebugName(){
        return "Not Defined!";
    }
    virtual void CreateVarWindow(int cId,Vec2I W){
       ImGui::Begin((GetDebugName()+"##"+std::to_string(cId)).c_str());
        ImGui::SetWindowPos(ImVec2(0,W.Y-200));
        ImGui::SetWindowSize(ImVec2(200,200));
       ImGui::Text("No Variables");
       ImGui::End();
    }

    virtual void SetPointers(Brush *Br,Material *M,GpuLights *L,DISPLAY *D,Vec3 *CamP,MapKey *KeyBinds,std::vector<std::unique_ptr<Ent>> *ents,
                             MapTransition *Tr,EngineMouse *EMouse, Ent *self){
        Brushes = Br;
        Materials = M;
        LightsPtr = L;
        Display = D;
        CamPos = CamP+0;
        CamRot = CamP+1;
        CamRotVec = CamP+2;
        UserKeyBind = KeyBinds;
        Ents = ents;
        Transition = Tr;
        Mouse = EMouse;
        Self = self;
    }
    virtual void SetT(float T){
        Time = T;
    }
    virtual void SetPos(Vec3 V){
        Pos = V;
    }
    virtual void SetRot(Vec3 V){
        Rot = V;
    }
    virtual void SetScale(Vec3 V){
        Scale = V;
    }
    virtual Vec3 GetPos(){
        return Pos;
    }
    virtual Vec3 GetScale(){
        return Scale;
    }
    virtual Vec3 GetRotation(){
        return Rot;
    }

    virtual std::string GetName(){
        return Name;
    }
    virtual void SetName(std::string N){
        Name = N;
    }

    virtual void SetBoundingBoxPos(Vec3 Pos[2]){
        BoundingBox[0] = Pos[0];
        BoundingBox[1] = Pos[1];

        float tmp = 0;

        if(BoundingBox[1].X < BoundingBox[0].X){
            //swap
            tmp = BoundingBox[1].X;
            BoundingBox[1].X = BoundingBox[0].X;
            BoundingBox[0].X = tmp;
        }
        if(BoundingBox[1].Y < BoundingBox[0].Y){
            //swap
            tmp = BoundingBox[1].Y;
            BoundingBox[1].Y = BoundingBox[0].Y;
            BoundingBox[0].Y = tmp;
        }
        if(BoundingBox[1].Z < BoundingBox[0].Z){
            //swap
            tmp = BoundingBox[1].Z;
            BoundingBox[1].Z = BoundingBox[0].Z;
            BoundingBox[0].Z = tmp;
        }
    }

    virtual void SetBoundingBoxSize(Vec3 Size){
        BoundingBox[0] = Vec3Subtract(Pos,Vec3Multiply(Size,{0.5,0.5,0.5}));
        BoundingBox[1] = Vec3Add(Pos,Vec3Multiply(Size,{0.5,0.5,0.5}));


    }

    void SetWeight(float Kg){
        weight = Kg;
    }
    float GetWeight(){
        return weight;
    }
    float GetForce(float G){
        return weight*(G/1000);
        //F = mG
        // g/1000 converts mm/s to m/s
    }
    Vec3 GetForceVec(Vec3 G){
        return Vec3Multiply({weight,weight,weight}, Vec3Divide(G,{1000,1000,1000}));
        //F = mG
        // g/1000 converts mm/s to m/s
    }
    Vec3 GetMomentum(){
        return Vec3Multiply({weight,weight,weight}, Vec3Divide(Vel,{1000,1000,1000}));
        //F = m(v/1000)
        // v/1000 converts mm/s to m/s
    }

    void KillSelf(){
        //kills object as soon as possible
        Kill = true;
    }
    bool ObjectNeedsToBeKilled(){
        return Kill;
    }

    virtual bool ThinkCheck(float TPS){
        if(ThinkTimer >0) {
            ThinkTimer = ThinkTimer - (1.0f / TPS);
            return false;
        }
            return true;
    }
    virtual void SetThinkTimer(float Val){
        ThinkTimer = Val;
    }

    virtual float Think(float TPS){

        //think function for your ent
        return 0;//time to the next think (sec)
    }
    virtual void OnFire(Ent *activator,Ent *caller){
        //Called when ent is triggered by another ent

    }
    virtual void OnDamage(Ent *activator,Ent *caller){
        //Called when ent is taking damage

    }
    virtual void OnInteract(Ent *activator,Ent *caller){
        //Called when player presses "E"

    }
    virtual void OnKill(Ent *activator,Ent *caller){
        //Called when entity must be killed

    }
    virtual void OnPlayerDeath(Ent *activator,Ent *caller){
        //Called when player dies

    }
    virtual void OnPlayerShoot(Ent *activator,Ent *caller){
        //Called when player shoots

    }
    virtual void OnMapStart(){
        //Called when map starts (1st tick)

    }
    virtual void Save(std::ofstream &File){
        //Called when save is created
        //std::cout << "Save\n";
    }
    virtual void Load(std::ifstream &File){
        //Called when loading object
        //std::cout << "Load\n";
    }

    virtual void Render3D(){
        //Called when rendering 3d

    }
    virtual void Render2D(){
        //Called when rendering 2d

    }
    virtual void PreRender(){
        //Called when rendering (3d) begins

    }

    virtual void SetVar(std::string Var,std::string Val){
        //called when map is loaded with trenchbroom and var needs to be set
        //low case

    }

    virtual void addVel(Vec3 V){
        Vel = Vec3Add(Vel,V);
    }

    virtual void ShadowPass(Vec3 LightPos,Vec3 LightSize,Vec3 LightDir,GLuint Shader){
        // called when 3d shadows are baked
        //render geometry with a special shader here
    }
    virtual void Cleanup(){
        // called when engine shuts down
    }
};

#endif

```

#### EntUSer.h
this file is mainly used for saving ents/loading

```
//
// Created by kitaS24 on 22.08.2025.
//

#ifndef ENGINE7_ENTUSER_H
#define ENGINE7_ENTUSER_H

bool EntCreate(std::string Str,std::vector<std::unique_ptr<Ent>> &Ent){
    if(Str == "Particle"){
        Ent.push_back(std::make_unique<Particle>());
        return true;
    }
    if(Str == "Light"){
        Ent.push_back(std::make_unique<Light>());
        return true;
    }
    if(Str == "Player"){
        Ent.push_back(std::make_unique<Player>());
        return true;
    }
    if(Str == "WorldRender"){
        Ent.push_back(std::make_unique<WorldRender>());
        return true;
    }
    return false;
}

void EntLoadCreate(std::ifstream &File,std::vector<std::unique_ptr<Ent>> &Ent){
    unsigned int Ents = 0;
    char NameData[64] = {};
    std::string NameStr = "";
    File.read(reinterpret_cast<char *>(&Ents), sizeof(Ents));
    for (int i = 0; i < Ents; ++i) {
        File.read(reinterpret_cast<char *>(&NameData), sizeof(NameData));
        NameStr = "";
        for (int j = 0; j < 64; ++j) {
            if(NameData[j] == 0){
                break;
            }else{
                NameStr.append(1,NameData[j]);
            }
        }
        EntCreate(NameStr,Ent);
    }
}


#endif //ENGINE7_ENTUSER_H

```

#### GameEnt.cpp

```
#include "RenderBrushEnt.cpp"
#include "PlayerEnt.cpp"
#include "LightEnt.cpp"
#include "particleEnt.cpp"
```

#### GameSubsys.cpp
this file can be empty unless you add your custom SubSys\
or it can just have this
```
//subsys (level 1)

//already includes
/*
#include "CreateBrush.cpp"
#include "Collision.cpp"
#include "Raycast.cpp"
#include "Light.cpp"
#include "Particle.cpp"
#include "TextFunctions.cpp"
#include "TextureLoad.cpp"
#include "AL_Setup.cpp"
#include "SoundEngine.cpp"
#include "EntName.cpp"
 */
```

#### textures/textures.ini
one texture example
```
[material]
TestMaterial

[TestMaterial]
base = textures/TestMaterial.bmp
data = textures/TestMaterialDt.bmp
vert = shaders/base.vert.glsl
frag = shaders/pbr.frag.glsl
metal = 0
SpecR = 0.510
SpecG = 0.510
SpecB = 0.510
```

#### main.cpp

```
#include <iostream>
#include "Core.cpp"
int main() {
    //Engine();
    Engine Game;

    Game.Setup();
    Game.SetSwapInterval(1);

    Game.CompileTrenchBroomMap("PipeMap.obj","PipeMap.map","saves/test1.gems","textures/textures.ini");

    while(Game.Frame()){}

    Game.Cleanup();
    return 0;
}
```


# Project structure

### just check

```
├───Build
│   ├───CMakeFiles
│   ├───saves
│   ├───shaders
│   └───textures
├───Engine
│   ├───Core
│   ├───Ents
│   ├───Import
│   ├───include
│   │   ├───CompiledOpenAlDll
│   │   ├───GLEW
│   │   ├───GLFW
│   │   ├───ImGui
│   │   │   ├───backends
│   │   │   └───misc
│   │   │       ├───cpp
│   │   │       ├───debuggers
│   │   │       ├───fonts
│   │   │       ├───freetype
│   │   │       └───single_file
│   │   └───OpenAl
│   ├───licenses
│   │   ├───GLEW
│   │   ├───GLFW
│   │   ├───ImGui
│   │   ├───OpenAl
│   │   └───SimpleGl
│   └───subsys
│       └───OpenAl
├───game

```

### engine7 project (compresses,check `game/` files)

```
├───Build
│   ├───saves
│   ├───shaders
│   ├───textures
│   └───OpenAL32.dll
├───Engine
├───game
│   ├───EntManager.h
│   ├───EntUser.h
│   ├───GameEnt.cpp
│   └───GameSubsys.cpp

```