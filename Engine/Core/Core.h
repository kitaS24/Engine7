//
// Created by kitaS24 on 18.08.2025.
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

#ifndef ENGINE7_CORE_H
#define ENGINE7_CORE_H

#define Ent_OnFireCall 1
#define Ent_OnDamageCallCall 2
#define Ent_OnKillCall 3
#define Ent_OnPlayerDeathCall 4
#define Ent_OnPlayerShootCall 5

#define Engine_Max_Brushes 1024
#define Engine_Max_Materials 256
#define Engine_Max_Lights 512

#define Deg_To_Rad 0.01745329251994329576923690768488612713442871888542
#define Rad_To_Deg  57.29577951308232087679815481410517033240547246656432

#define Engine_G -9800.0f

#define Engine_Key_Save GLFW_KEY_F6
#define Engine_Key_Load GLFW_KEY_F9

//mouse btns
#define Engine_LM 1001
#define Engine_RM 1000
//MapSpecial keys Into ASCII
#define Engine_ASCII_LM 201
#define Engine_ASCII_RM 200

//
#define Engine_Map_Scale 25.4

//
#define Engine_MaxSpotLights 64

#endif //ENGINE7_CORE_H
