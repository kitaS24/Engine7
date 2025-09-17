//
// Created by kitaS24 on 24.08.2025.
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

class TextSplit{
    std::string Text;
    char Divider = 0;
public:
    void SetStr(std::string Str){
        Text = Str;
    }
    void SetDivider(char C){
        Divider = C;
    }
    std::string GetText(unsigned int p){
        unsigned int InnerP = 0;
        std::string o = "";
        for (int i = 0; i < Text.length(); ++i) {
            if(Text.at(i) == Divider){

                if(InnerP == p){
                    return o;
                }
                InnerP = InnerP+1;
                o="";
            }else{
                o.append(1,Text.at(i));
            }
        }
        return o;
    }

    //returns if out of bounds
    bool GetTextOOB(unsigned int p){
        unsigned int InnerP = 0;
        std::string o = "";
        for (int i = 0; i < Text.length(); ++i) {
            if(Text.at(i) == Divider){

                if(InnerP == p){
                    return false;
                }
                InnerP = InnerP+1;
                o="";
            }else{
                o.append(1,Text.at(i));
            }
        }
        if(InnerP == p){
            return false;
        }
        return true;
    }
};