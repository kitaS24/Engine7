//
// Created by kitaS24 on 26.08.2025.
//

#include "EntUser.h"

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

void SaveBrushes(Brush *Brushes, std::ofstream &File){
    int BrushN = 0;
    for (int i = 0; i < Engine_Max_Brushes; ++i) {
        if(!((*(Brushes+i)).Active)){
            BrushN = i+1;
        }
    }
    File.write(reinterpret_cast<char *>(&BrushN), sizeof(BrushN));
    for (int i = 0; i < BrushN; ++i) {
        File.write(reinterpret_cast<char *>(&(*(Brushes+i))), sizeof((*(Brushes+i))));
    }
}
void LoadBrushes(Brush *Brushes, std::ifstream &File){
    int BrushN = 0;
    File.read(reinterpret_cast<char *>(&BrushN), sizeof(BrushN));
    for (int i = 0; i < BrushN; ++i) {
        File.read(reinterpret_cast<char *>(&(*(Brushes+i))), sizeof((*(Brushes+i))));
        //File.write(reinterpret_cast<char *>(&(*(Brushes+i))), sizeof((*(Brushes+i))));
    }
}

void EngineSave(std::vector<std::unique_ptr<Ent>> *LevelEnt,Brush *Brushes,std::string FileName){
    std::ofstream SaveMap{FileName, std::ios::binary};
    SaveBrushes(Brushes,SaveMap);
    EntSaveAddObjName(*LevelEnt,SaveMap);
    EntSave(*LevelEnt,SaveMap);
    SaveMap.close();
}
void EngineLoad(std::vector<std::unique_ptr<Ent>> *LevelEnt,Brush *Brushes,std::string FileName){
    std::ifstream LoadMap{FileName, std::ios::binary};
    if (!LoadMap.is_open()) {
        std::cout << "File not open\n";
        std::cout << "File is absent from path : "<<"saves/test1.gems" <<"\n";
        //exit(3);
        return;
    }
    LoadBrushes(Brushes,LoadMap);
    (*LevelEnt).clear();
    EntLoadCreate(LoadMap,*LevelEnt);
    EntLoad(*LevelEnt,LoadMap);
}