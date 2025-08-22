//
// Created by kitaS24 on 22.08.2025.
//

#ifndef ENGINE7_ENTUSER_H
#define ENGINE7_ENTUSER_H

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
        if(NameStr == "Particle"){
            LevelEnt.push_back(std::make_unique<Particle>());
        }
        if(NameStr == "Light"){
            LevelEnt.push_back(std::make_unique<Light>());
        }
        if(NameStr == "Player"){
            LevelEnt.push_back(std::make_unique<Player>());
        }
        if(NameStr == "WorldRender"){
            LevelEnt.push_back(std::make_unique<WorldRender>());
        }
    }
}

#endif //ENGINE7_ENTUSER_H
