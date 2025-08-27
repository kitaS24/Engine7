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
    Brush B = {};
    BrushSave BS = {};
    for (int i = 0; i < Engine_Max_Brushes; ++i) {
        BrushN = i;
        if(!((*(Brushes+i)).Active)){
            break;
        }
    }
    File.write(reinterpret_cast<char *>(&BrushN), sizeof(BrushN));
    for (int i = 0; i < BrushN; ++i) {

        B = *(Brushes+i);
        BS.Planes = B.Planes;
        BS.CollisionType = B.CollisionType;
        BS.Active = B.Active;
        BS.TransformMatrix = B.TransformMatrix;
        for (int j = 0; j < 3; ++j) {
            BS.RotationMatrix[j] = B.RotationMatrix[j];
        }
        BS.Rotation = B.Rotation;
        BS.BoundingBox1 = B.BoundingBox1;
        BS.BoundingBox2 = B.BoundingBox2;

        File.write(reinterpret_cast<char *>(&BS), sizeof(BrushSave));
        for (int j = 0; j < B.Planes; ++j) {
            File.write(reinterpret_cast<char *>(&B.BrushPlane[j]), sizeof(BrushSave));
        }
    }
}
void LoadBrushes(Brush *Brushes, std::ifstream &File){
    int BrushN = 0;

    BrushSave BS = {};
    File.read(reinterpret_cast<char *>(&BrushN), sizeof(BrushN));
    for (int i = 0; i < BrushN; ++i) {
        Brush &B = *(Brushes+i);

        File.read(reinterpret_cast<char *>(&BS), sizeof(BrushSave));

        B.Planes = BS.Planes;
        B.CollisionType = BS.CollisionType;
        B.Active = BS.Active;
        B.TransformMatrix = BS.TransformMatrix;
        for (int j = 0; j < 3; ++j) {
            B.RotationMatrix[j] = BS.RotationMatrix[j];
        }
        B.Rotation = BS.Rotation;
        B.BoundingBox1 = BS.BoundingBox1;
        B.BoundingBox2 = BS.BoundingBox2;

        for (int j = 0; j < B.Planes; ++j) {
            File.read(reinterpret_cast<char *>(&B.BrushPlane[j]), sizeof(BrushSide));
        }

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