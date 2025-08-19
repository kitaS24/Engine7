//
// Created by kitaS24 on 18.08.2025.
//

void EntList(std::vector<std::unique_ptr<Ent>> &Ent,unsigned int &DebugEntV,Vec2I WindowSize){
    ImGui::Begin("ents");
    ImGui::SetWindowPos(ImVec2(0,0));
    ImGui::SetWindowSize(ImVec2(200,WindowSize.Y-200));
    for (int i = 0; i < Ent.size(); i++) {
        if(ImGui::Button((Ent[i]->GetDebugName()+"##"+std::to_string(i)).c_str())){
            DebugEntV = i;
        }
    }
    ImGui::End();
    for (int i = 0; i < Ent.size(); i++) {
        if(DebugEntV == i) {
            Ent[i]->CreateVarWindow(i,WindowSize);
        }
    }
}

void EntThink(std::vector<std::unique_ptr<Ent>> &Ent,float TPS){
    for (int i = 0; i < Ent.size(); i++) {
        if(Ent[i]->ThinkCheck(TPS)){
            Ent[i]->SetThinkTimer(Ent[i]->Think());
        }
    }
}

void EntUpdate(std::vector<std::unique_ptr<Ent>> &Ent,float T){
    for (int i = 0; i < Ent.size(); i++) {
            Ent[i]->SetT(T);
    }
}

void EntUpdatePointers(std::vector<std::unique_ptr<Ent>> &Ent,Brush *Br,Material *Mt,GpuLights *L){
    for (int i = 0; i < Ent.size(); i++) {
            Ent[i]->SetRenderPointer(Br,Mt,L);
    }
}

void EntPreRender(std::vector<std::unique_ptr<Ent>> &Ent){
    for (int i = 0; i < Ent.size(); i++) {
        Ent[i]->PreRender();
    }
}

void EntRender3D(std::vector<std::unique_ptr<Ent>> &Ent){
    for (int i = 0; i < Ent.size(); i++) {
        Ent[i]->Render3D();
    }
}