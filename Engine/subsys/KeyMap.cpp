//
// Created by kitaS24 on 22.08.2025.
//

// Copyright (c) 2025 kitaS24

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