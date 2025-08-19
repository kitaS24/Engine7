//
// Created by kitaS24 on 18.08.2025.
//

#ifndef ENGINE7_ENTMANAGER_H
#define ENGINE7_ENTMANAGER_H
class Ent{
private:
    float ThinkTimer;
protected:
    Brush *Brushes;
    Material *Materials;
    GpuLights *LightsPtr;
    Vec3 Pos;
    Vec3 Scale;
    float Time;
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

    virtual void SetRenderPointer(Brush *Br,Material *M,GpuLights *L){
        Brushes = Br;
        Materials = M;
        LightsPtr = L;
    }
    virtual void SetT(float T){
        Time = T;
    }
    virtual void SetPos(Vec3 V){
        Pos = V;
    }
    virtual void SetScale(Vec3 V){
        Scale = V;
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

    virtual float Think(){

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
    virtual void OnMapStart(Ent *activator,Ent *caller){
        //Called when player shoots

    }
    virtual void Save(){
        //Called when save is created

    }
    virtual void Load(){
        //Called when loading object

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
};

#endif //ENGINE7_ENTMANAGER_H
