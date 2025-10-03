//
// Created by kitaS24 on 03.10.2025.
//

Ent* GetEntByName(std::vector<std::unique_ptr<Ent>> &Ents,std::string Name){
    for (int i = 0; i < Ents.size(); i++) {
        if (Ents[i]) {
            if(Ents[i]->GetName() == Name){
                return Ents[i].get();
            }
        }
    }
    return nullptr;
}