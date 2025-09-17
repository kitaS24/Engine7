//
// Created by kitaS24 on 22.08.2025.
//

/*
    Engine7 - a GoldSrc like engine
    Copyright (C) 2025  kitaS24

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
