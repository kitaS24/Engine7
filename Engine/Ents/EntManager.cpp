//
// Created by kitaS24 on 18.08.2025.
//

#include "EntUser.h"

void EntList(std::vector<std::unique_ptr<Ent>> &Ent,unsigned int &DebugEntV,Vec2I WindowSize){
    ImGui::Begin("ents");
    ImGui::SetWindowPos(ImVec2(0,0));
    ImGui::SetWindowSize(ImVec2(200,WindowSize.Y-200));
    for (int i = 0; i < Ent.size(); i++) {
        if(Ent[i]) {
            if (ImGui::Button((Ent[i]->GetDebugName() + "##" + std::to_string(i)).c_str())) {
                DebugEntV = i;
            }
        }
    }
    ImGui::End();
    for (int i = 0; i < Ent.size(); i++) {
        if(Ent[i]) {
            if (DebugEntV == i) {
                Ent[i]->CreateVarWindow(i, WindowSize);
            }
        }
    }
}

void EntThink(std::vector<std::unique_ptr<Ent>> &Ent,float TPS){
    for (int i = 0; i < Ent.size(); i++) {
        if (Ent[i]) {
            if (Ent[i]->ThinkCheck(TPS)) {
                Ent[i]->SetThinkTimer(Ent[i]->Think(TPS));
            }
        }
    }
}

void EntUpdate(std::vector<std::unique_ptr<Ent>> &Ent,float T){
    for (int i = 0; i < Ent.size(); i++) {
        if (Ent[i]) {
            Ent[i]->SetT(T);
            }
    }
}

void EntUpdatePointers(std::vector<std::unique_ptr<Ent>> &Ent,Brush *Br,Material *Mt,GpuLights *L,DISPLAY *D,Vec3 *CamPos,MapKey *Key){
    for (int i = 0; i < Ent.size(); i++) {
        if (Ent[i]) {
            Ent[i]->SetPointers(Br,Mt,L,D,CamPos,Key);
            }
    }
}

void EntPreRender(std::vector<std::unique_ptr<Ent>> &Ent){
    for (int i = 0; i < Ent.size(); i++) {
        if (Ent[i]) {
            Ent[i]->PreRender();
        }
    }
}

void EntRender3D(std::vector<std::unique_ptr<Ent>> &Ent){
    for (int i = 0; i < Ent.size(); i++) {
        if (Ent[i]) {
            Ent[i]->Render3D();
        }
    }
}

void EntRender2D(std::vector<std::unique_ptr<Ent>> &Ent){
    for (int i = 0; i < Ent.size(); i++) {
        if (Ent[i]) {
            Ent[i]->Render2D();
        }
    }
}


void EntSave(std::vector<std::unique_ptr<Ent>> &Ent,std::ofstream &File){
    for (int i = 0; i < Ent.size(); i++) {
        if (Ent[i]) {
            Ent[i]->Save(File);
        }
    }
}
void EntSaveAddObjName(std::vector<std::unique_ptr<Ent>> &Ent, std::ofstream &File){
    std::string N = "";
    char cN[64] ="";//char name
    unsigned int Ents = Ent.size();
    File.write(reinterpret_cast<char *>(&Ents), sizeof(Ents));
    for (int i = 0; i < Ent.size(); i++) {
        if (Ent[i]) {
            N = Ent[i]->GetDebugName();
            for (int j = 0; j < 64; ++j) {
                cN[j] = 0;
            }
            for (int j = 0; j < 64 && j < N.length(); ++j) {
                cN[j] = N.at(j);
            }
            File.write(reinterpret_cast<char *>(&cN), 64);
        }
    }
}
void EntLoad(std::vector<std::unique_ptr<Ent>> &Ent,std::ifstream &File){
    for (int i = 0; i < Ent.size(); i++) {
        if (Ent[i]) {
            Ent[i]->Load(File);
        }
    }
}

//
void KillAllRequestedObjs(std::vector<std::unique_ptr<Ent>> &Ent){
    for (int i = 0; i < Ent.size(); i++) {
        if (Ent[i]) {
            if (Ent[i]->ObjectNeedsToBeKilled()) {
                //EntEraseByPointer(Ent,Ent[i].get());
                Ent[i].reset();
                return;
            }
        }
    }

}