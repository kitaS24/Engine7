//
// Created by kitaS24 on 18.08.2025.
//

//debug
void EntList(std::vector<std::unique_ptr<Ent>> &Ent,unsigned int &DebugEntV,Vec2I WindowSize,DISPLAY D){
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
    ImGui::Text(("FPS:"+std::to_string(D.FPS)).c_str());
    ImGui::End();
    for (int i = 0; i < Ent.size(); i++) {
        if(Ent[i]) {
            if (DebugEntV == i) {
                Ent[i]->CreateVarWindow(i, WindowSize);
            }
        }
    }
}

//ent tick/call
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

void EntUpdatePointers(std::vector<std::unique_ptr<Ent>> &Ent,Brush *Br,Material *Mt,GpuLights *L,DISPLAY *D,Vec3 *CamPos,MapKey *Key,MapTransition *Tr ){
    for (int i = 0; i < Ent.size(); i++) {
        if (Ent[i]) {
            Ent[i]->SetPointers(Br,Mt,L,D,CamPos,Key,&Ent,Tr);
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
void EntCleanupCall(std::vector<std::unique_ptr<Ent>> &Ent){
    for (int i = 0; i < Ent.size(); i++) {
        if (Ent[i]) {
            Ent[i]->Cleanup();
        }
    }
}
void EntOnMapStartCall(std::vector<std::unique_ptr<Ent>> &Ent){
    for (int i = 0; i < Ent.size(); i++) {
        if (Ent[i]) {
            Ent[i]->OnMapStart();
        }
    }
}



//kill 1st object that needs to be killed, (idk why I return)
void KillAllRequestedObjs(std::vector<std::unique_ptr<Ent>> &Ent){
    for (int i = 0; i < Ent.size(); i++) {
        if (Ent[i]) {
            if (Ent[i]->ObjectNeedsToBeKilled()) {
                Ent[i].reset();
                return;
            }
        }
    }

}