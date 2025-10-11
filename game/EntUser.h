//
// Created by kitaS24 on 22.08.2025.
//

// Copyright (c) 2025 kitaS24

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
