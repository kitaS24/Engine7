# Readme for the GameEngine 7
***
## here is a todo list

### DONE
* scripting with classes
* lighting system (point,spot)
* collisions
* world raycast
* particle system
* mappable keys
* level loading/saving (quick save/load)
* PBR
* Flood Light (with shadows)
* trenchbroom map loading and saving (obj,.map)
* _level loading_
* GUI (ImGUI)
* audio
* player controller (DEMO)
### WORKING ON
### TODO

* static prop creation,compilation  **[CANCELED]**
* GUI   **[CANCELED]**

## Entity Functions update (scripting)

| Function         | In                                                       | return      | Description                                                                                      |
|------------------|----------------------------------------------------------|-------------|--------------------------------------------------------------------------------------------------|
| Think            | float TPS                                                | float (sec) | called with return delay                                                                         |
| Save             | std::ofstream &File                                      | void        | called when saving, save your important vars here                                                |
| Load             | std::ifstream &File                                      | void        | called when loading, load your important vars here **MUST BE SAME**                              |
| Render3D         |                                                          | void        | called when rendering 3d                                                                         |
| Render2D         |                                                          | void        | called when rendering 2d                                                                         |
| PreRender        |                                                          | void        | called when rendering (3d) begins                                                                |
| SetVar           | std::string Var,std::string Val                          | void        | called when map is loaded with trenchbroom and var needs to be set in the entity                 |
| ShadowPass       | Vec3 LightPos,Vec3 LightSize,Vec3 LightDir,GLuint Shader | void        | called when 3d shadows are baked, render your geometry with the **Shader** for it to cast shadow |
| Cleanup          |                                                          | void        | called before engine shuts down                                                                  |
| OnMapStart       |                                                          | void        | called when map starts (1st tick)                                                                |
| GetDebugName     |                                                          | std::string | called to request entity debug name                                                              |
| CreateVarWindow  | int cId,Vec2I W                                          | void        | called to draw debug window                                                                      |

## Entity Functions

| Function    | In                            | return | Description                                                                                                       |
|-------------|-------------------------------|--------|-------------------------------------------------------------------------------------------------------------------|
| KillSelf    |                               | void   | Flags Entity to be killed (public)                                                                                |
| GetPos      |                               | Vec3   | Returns Entity Pos (public)                                                                                       |
| GetScale    |                               | Vec3   | Returns Entity Scale (public)                                                                                     |
| GetRotation |                               | Vec3   | Returns Entity Rotation (public)                                                                                  |
| SetPos      | Vec3                          | void   | Sets Entity Pos (public)                                                                                          |
| SetRot      | Vec3                          | void   | Sets Entity Rot (public)                                                                                          |
| SetScale    | Vec3                          | void   | Sets Entity Scale (public)                                                                                        |
| addVel      | Vec3                          | void   | Adds Velocity to the entity velocity (public)                                                                     |
| ChangeMap   | std::string Map,bool IsNewMap | void   | Sets Map for engine to load. bool IsNewMap is used when loading new map (not quicksave),OnMapStart will be called |
| SetWeight   | float Kg                      | void   | Sets weight in KG                                                                                                 |
| GetWeight   |                               | float  | Gets weight in KG                                                                                                 |
| GetForce    | float G                       | float  | Returns force -Y                                                                                                  |
| GetForceVec | Vec3 G                        | Vec3   | Returns force Vec                                                                                                 |
| GetMomentum |                               | Vec3   | Returns momentum (from ent Vel)                                                                                   |

## Entity Events

when calling pass 2 arguments
* Ent *activator | original activator
* Ent *caller | last activator (self)

| Function       | In                          | return | Description                                 |
|----------------|-----------------------------|--------|---------------------------------------------|
| OnFire         | Ent *activator,Ent *caller  | void   | Called when ent is triggered by another ent |
| OnDamage       | Ent *activator,Ent *caller  | void   | Called when ent is taking damage            |
| OnInteract     | Ent *activator,Ent *caller  | void   | Called when player presses "E"              |
| OnKill         | Ent *activator,Ent *caller  | void   | Called when entity must be killed           |
| OnPlayerDeath  | Ent *activator,Ent *caller  | void   | Called when player dies                     |
| OnPlayerShoot  | Ent *activator,Ent *caller  | void   | Called when player shoots                   |

## Entity Variables/Pointers

| Type                                | Name        | Description                                                                                                               |
|-------------------------------------|-------------|---------------------------------------------------------------------------------------------------------------------------|
| Brush *                             | Brushes     | Level brushes (pointer)                                                                                                   |
| Material *                          | Materials   | Loaded Materials                                                                                                          |
| Vec3                                | Pos         | Entity Position                                                                                                           |
| Vec3                                | Rot         | Entity Rotation                                                                                                           |
| Vec3                                | Vel         | Entity Velocity                                                                                                           |
| Vec3                                | Scale       | Entity Scale                                                                                                              |
| float                               | Time        | Time From Engine Start                                                                                                    |
| DISPLAY *                           | Display     | Display Struct with data for display                                                                                      |
| Vec3 *                              | CamPos      | Camera Position                                                                                                           |
| Vec3 *                              | CamRot      | Camera Rotation                                                                                                           |
| Vec3 *                              | CamRotVec   | Camera Look Vector                                                                                                        |
| MapKey *                            | UserKeyBind | User KeyBinds (class. use Map(unsigned char Key,int glfwVal) to bind, use key(unsigned char Key) to get mapped key state) |
| std::vector<std::unique_ptr<Ent>> * | Ents        | Pointer to the list with all entities                                                                                     |
| MapTransition *                     | Transition  | Pointer to struct for level transition                                                                                    |


## SubSystem Functions


| FunctionName                     | In                                                                                                                                                 | Out       | Description                                                                                        |
|----------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------|-----------|----------------------------------------------------------------------------------------------------|
| RotateBrush()                    | Brush &Br,Vec3 SetRot,Vec3 RotPoint                                                                                                                | void      | sets rotation for the brush                                                                        |
| RenderSideRotate()               | BrushSide Br,Vec3 Transform[3],Vec3 Matrix[3]                                                                                                      | BrushSide | rotates brush side with matrices (including vert)                                                  |
| CollisionSideRotate()            | BrushSide Br,Vec3 Transform[3],Vec3 Matrix[3]                                                                                                      | BrushSide | rotates brush side with matrices (ONLY normals, Collision Pos)                                     |
| AddLight()                       | GpuLights *L,Vec3 Pos,Vec3 Color,Vec3 Dir,float InnerCone,float OuterCone                                                                          | void      | adds light to the scene                                                                            |
| AddFloodLight()                  | GpuLights *L,Vec3 Pos,Vec3 Color,Vec3 Size,Vec3 Dir,GLuint DT                                                                                      | void      | adds floodlight to the scene                                                                       |
| InitFloodLight()                 | GLuint &tx,GLuint &fbo,GLuint &rbo                                                                                                                 | void      | creates floodlight texture/setup.Provide 3 GLuint s                                                |
| UpdateFloodLight()               | Vec3 LightPos,Vec3 LightSize,Vec3 LightDir,GLuint Shader,Vec2 WindowSize,std::vector<std::unique_ptr<Ent>> &Ent,GLuint &tx,GLuint &fbo,GLuint &rbo | void      | renders world to the flood texture                                                                 |
| CollisionWorld()                 | Brush *Brushes,unsigned int CheckBrushes,Vec3 Point                                                                                                | bool      | returns TRUE if point is inside of any brush                                                       |
| CollisionWorldArea()             | Brush *Brushes,unsigned int CheckBrushes,Vec3 Point,Vec3 HSize                                                                                     | bool      | returns TRUE if AABB area is inside of any brush                                                   |
| AABBtoAABB()                     | Vec3 A1,Vec3 A2,Vec3 B1,Vec3 B2                                                                                                                    | bool      | AABB to AABB                                                                                       |
| AABBtoAABBSmart()                | Vec3 A1,Vec3 A2,Vec3 B1,Vec3 B2                                                                                                                    | bool      | Same as AABB to AABB ,but can flip pA and pB so AABB always works                                  |
| CreateBrushBoundingBox()         | Brush &Br                                                                                                                                          | void      | Updates Brush Bounding Box by vert                                                                 |
| CreateBrushBoundingBoxNormals()  | Brush &Br                                                                                                                                          | void      | Updates Brush Bounding Box by collision box                                                        |
| CreateBrushBoundingBoxAll()      | Brush &Br                                                                                                                                          | void      | does both: CreateBrushBoundingBox and CreateBrushBoundingBoxNormals                                |
| MapKey.Map()                     | unsigned char Key,int glfwVal                                                                                                                      | void      | Maps Key(char) to GLFW value. Example: at start 'A'=='A', can be changed so, 'A'='B'               |
| MapKey.key()                     | unsigned char Key                                                                                                                                  | bool      | Set Key to key before it was mapped                                                                |
| MapKey.SetupGlfwKeys()           |                                                                                                                                                    | void      | Sets All keys to initial val ('A'=='A')                                                            |
| RenderParticle()                 | Vec3 *Pos,unsigned int RenderParticles,Vec3 Rot,Vec2 Size,Material *Material,GpuLights *L,unsigned int LN,Vec3 CamPos,Vec4 Color                   | void      | Renders Particles Facing to the camera (can render any amount of particles, is material is shared) |
| ShadowRenderParticle()           | Vec3 *Pos,unsigned int RenderParticles,Vec3 Rot,Vec2 Size,GLuint Shader,Vec3 LightPos,Vec3 LightSize,Vec3 LightDir                                 | void      | Allows for particles to have shadows                                                               |
| WorldRaycast()                   | Vec3 Start,Vec3 End,Vec3 Size,float SampleRate,Brush *Brushes                                                                                      | float     | Returns Distance to any brush in a level. Input:Start,End pos                                      |
| SoundEngineSource.Setup()        | Vec3 P                                                                                                                                             | void      | Init, set audio pos                                                                                |
| SoundEngineSource.UpdatePos()    | Vec3 P                                                                                                                                             | void      | set audio pos                                                                                      |
| SoundEngineSource.UpdateSpeed()  | float Speed                                                                                                                                        | void      | Sets audio play speed                                                                              |
| SoundEngineSource.LoadWavSound() | std::string filename,float Vol                                                                                                                     | bool      | Loads WAV file (UNCOMPRESSED,Audacity can be used for that)                                        |
| SoundEngineSource.Pause()        |                                                                                                                                                    | void      | Pauses the sound                                                                                   |
| SoundEngineSource.UnloadSound()  |                                                                                                                                                    | void      | Unloads sound (OpenAL buffer)                                                                      |
| SoundEngineSource.Delete()       |                                                                                                                                                    | void      | Deletes source,Stops Audio,Unloads                                                                 |
| SoundEngineSource.Play()         | float SoundVolume                                                                                                                                  | void      | Plays the sound                                                                                    |


## Building

CMakeLists doesn't build OpenAL and puts dll into the Build folder

1. Get Engine Folder or Example Engine7 Project
2. create files EntManager.h,EntUser.h,GameEnt.cpp,GameSubsys.cpp in game folder
3. setup files EntManager.h,EntUser.h,GameEnt.cpp,GameSubsys.cpp, example lower
4. add "texture", "shaders" folder to Build folder
5. "texture" folder must contain "textures.ini", example lower
6. "texture" folder must contain your textures
7. "shaders" folder must contain your shaders (Vertex,Fragment)

---

8. Compile OpenAL (openal-soft), guides can be found online
9. paste OpenAl32.dll file into the Build folder
10. if not taken from the example, copy basic engine code to "main.cpp"

Engine project **should** build

### For engine to work, copy example code into specified files

#### EntManager.h
```
//
// Created by kitaS24 on 18.08.2025.
//

#ifndef ENGINE7_ENTMANAGER_H
#define ENGINE7_ENTMANAGER_H

#include "structs.h"
#include "math.cpp"
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

    virtual void SetPointers(Brush *Br,Material *M,GpuLights *L,DISPLAY *D,Vec3 *CamP,MapKey *KeyBinds,std::vector<std::unique_ptr<Ent>> *Ent,
                             MapTransition *Tr){
        Brushes = Br;
        Materials = M;
        LightsPtr = L;
        Display = D;
        CamPos = CamP+0;
        CamRot = CamP+1;
        CamRotVec = CamP+2;
        UserKeyBind = KeyBinds;
        Ents = Ent;
        Transition = Tr;
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

#endif //ENGINE7_ENTMANAGER_H

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

file structure

```
├───BuildFolder
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

engine7 project 

```
├───BuildFolder
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



# TRENCHBROOM MAP BUILDING

**this step needs 2 files**
* .map
* .obj

to get obj use export>Wavefront OBJ...\
pass 2 files with "textures.ini"\
save is built into a function so map can be loaded faster with "gems" format\
example:
`Game.CompileTrenchBroomMap("PipeMap.obj","PipeMap.map","saves/test1.gems","textures/textures.ini");`

### what is .GEMS ?

`.gems` is a compiled map for engine7.\
`.gem` was a map format that stores Brushes and Entity data in binary

`.gems` was made more flexible, for any type of entity. (data isn't constrained to 64 bytes)\
by passing only `.gems` engine needs less time to load a level compared to `.map` or `.obj`

#### Format structure

1. int BrushN | Brush Number in a level
2. Brushes | (slightly compressed. Unused sides removed)
3. unsigned int EntN | Ent Number
4. every entity DEBUG name (64 bytes)
5. entity custom data. any format. Use Save Load function for that.


.gems can be built from `.map` AND `.obj` AT THE SAME TIME