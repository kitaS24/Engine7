//
// Created by kitaS24 on 25.08.2025.
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

#include <iostream>
#include <fstream>
class IniRead{
    std::string FileN;
    unsigned long long int FileIndex;

    std::string GetVarName(std::string Line){
        std::string o = "";
        for (int i = 0; i < Line.length(); ++i) {
            if(Line.at(i) == '='){
                return o;
            }
            if(Line.at(i) != ' ') {
                o.append(1, Line.at(i));
            }
        }
    }
    std::string GetVarVal(std::string Line){
        std::string o = "";
        bool Val = false;
        for (int i = 0; i < Line.length(); ++i) {
            if(Line.at(i) == '='){
                Val = true;
            }
            if(Val) {
                if (Line.at(i) != ' ' && Line.at(i) != '=') {
                    o.append(1, Line.at(i));
                }
            }
        }
        return o;
    }

public:

    void SearchHeader(std::string Filename,std::string Header){
        FileN =Filename;
        std::string Line;

        std::ifstream Read(Filename);
        FileIndex=0;
        while (getline(Read, Line)) {
            FileIndex = FileIndex+1;
            if("["+Header+"]" == Line){
                return;
            }

        }

        Read.close();
    }
    std::string ListHeaderContent(){
        std::string Line;
        unsigned long long int i=0;

        std::ifstream Read(FileN);
        //FileIndex=0;
        while (getline(Read, Line)) {
            i = i+1;
            if(i == FileIndex+1){
                if(Line.length() <1){
                    return "!not_found";
                }
                if(Line.at(0) == '['){
                    return "!not_found";
                }

                FileIndex = FileIndex+1;
                return Line;
            }
        }

        Read.close();
        return "!not_found";
    }

    std::string HeaderVar(std::string VarName){
        std::string Line;
        unsigned long long int i=0;

        std::ifstream Read(FileN);
        while (getline(Read, Line)) {
            i = i+1;
            if(i >= FileIndex+1){
                if(Line.at(0) == '['){
                    return "!not_found";
                }

                if(GetVarName(Line) == VarName){
                    return GetVarVal(Line);
                }

            }
        }

        Read.close();
        return "!not_found";
    }

};