//
// Created by kitaS24 on 18.08.2025.
//

#ifndef ENGINE7_ENTMANAGER_H
#define ENGINE7_ENTMANAGER_H

#include "structs.h"
#include <string>

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


    void ChangeMap(std::string Map,bool IsNewMap){
        (*Transition).MapName = Map;
        (*Transition).IsNewMap = IsNewMap;
        (*Transition).LoadMap = true;
    }
public:
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
