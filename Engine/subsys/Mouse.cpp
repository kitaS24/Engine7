//
// Created by kitaS24 on 20.09.2025.
//

#include <iostream>
#include "GLFW/glfw3.h"
#include "structs.h"

// Copyright (c) 2025 kitaS24

#ifndef ENGINE7_SubMouse_CPP
#define ENGINE7_SubMouse_CPP

class EngineMouse{
private:
    GLFWwindow* StoreWindow;

    Vec2 MousePos = {0,0};
    Vec2I Center = {0,0};
    bool BtnLeft = false;
    bool BtnRight = false;
    bool BtnAny = false;

    bool InMenu = false;

    float Sensitivity =0.3;

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
        EngineMouse *self = static_cast<EngineMouse*>(glfwGetWindowUserPointer(window));
        if(!self){return;}
        self->MousePos.X = xpos;
        self->MousePos.Y = ypos;
    }
    static void mouseBtn_callback(GLFWwindow* window, int button, int action, int mods) {
        EngineMouse *self = static_cast<EngineMouse*>(glfwGetWindowUserPointer(window));
        if(!self){return;}
        if(button == GLFW_MOUSE_BUTTON_LEFT && action){
            self->BtnLeft = true;
        }
        if(button == GLFW_MOUSE_BUTTON_LEFT && !action){
            self->BtnLeft = false;
        }

        if(button == GLFW_MOUSE_BUTTON_RIGHT && action){
            self->BtnRight = true;
        }
        if(button == GLFW_MOUSE_BUTTON_RIGHT && !action){
            self->BtnRight = false;
        }

        self->BtnAny = self->BtnLeft || self->BtnRight;

    }

public:

    void SetSens(float V){
        Sensitivity = V;
    }

    void SetupMouseCallBack(GLFWwindow* window,EngineMouse *Self){
        //std::cout << "SetCallback\n";
        StoreWindow = window;
        glfwSetWindowUserPointer(window,Self);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetMouseButtonCallback(window, mouseBtn_callback);
    }

    Vec2 GetMousePos(){
        return MousePos;
    }

    bool Right(){
        return BtnRight;
    }
    bool Left(){
        return BtnLeft;
    }
    bool Any(){
        return BtnAny;
    }

    // 2 functions so any function can flag as being in a menu, and others won't reset (no checks)
    void SetInMenu(){
        InMenu = true;
    }
    void ResetInMenu(){
        InMenu = false;
    }
    bool GetInMenu(){
        return InMenu;
    }
    //
    void CenterMouse(){
        int X=0;
        int Y=0;
        glfwGetWindowSize(StoreWindow, &X, &Y);
        Center.X = int(float(X) / 2.0f);
        Center.Y = int(float(Y) / 2.0f);
        glfwSetCursorPos(StoreWindow, Center.X, Center.Y);
    }
    Vec2 GetCenteredMouse(bool ApplySens){
        int X=0;
        int Y=0;
        glfwGetWindowSize(StoreWindow, &X, &Y);
        if(ApplySens){
            return {(MousePos.X - Center.X)*Sensitivity, (MousePos.Y - Center.Y)*Sensitivity};
        }else {
            return {MousePos.X - Center.X, MousePos.Y - Center.Y};
        }
    }

};

#endif