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

class MapKey{
    //custom values can be used (over 999)
private:
    DISPLAY *D;
   int KeyM[256];
public:
    //sets OpenGL display
    void UpdateWindow(DISPLAY* d){
            D = d;
    }
    //allows to map a key
    void Map(unsigned char Key,int glfwVal){
        KeyM[Key] = glfwVal;
    }
    //gets key state
    bool key(unsigned char Key){
        if(KeyM[Key] >999){
            if(KeyM[Key] == Engine_RM) {
                return (*D).Right && (*D).Pressed;
            }
            if(KeyM[Key] == Engine_LM) {
                return (*D).Left && (*D).Pressed;
            }
        }else {
            return glfwGetKey((*D).window, KeyM[Key]);
        }
    }
    //setups keys, for loop
    void SetupGlfwKeys(){
        for (int i = GLFW_KEY_A; i < GLFW_KEY_Z; ++i) {
            KeyM[i] = i;
            KeyM[i+32] = i;
        }
        KeyM[32] = GLFW_KEY_SPACE;
        KeyM[10] = GLFW_KEY_ENTER;

        KeyM[Engine_ASCII_RM] = Engine_RM;
        KeyM[Engine_ASCII_LM] = Engine_LM;
    }
};