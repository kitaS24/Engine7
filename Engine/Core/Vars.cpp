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

std::vector<std::unique_ptr<Ent>> LevelEnt;
unsigned int DebugEntView = 0;
Brush LevelBrushes[Engine_Max_Brushes] = {};
Material Materials[Engine_Max_Materials] = {};
GpuLights Lights = {};

DISPLAY D = {};
Vec3 Cam[3] = {};

bool SaveOrLoadKeyPress = false;

MapKey UserKeyBind;
OpenAl EngineAl;
MapTransition LevelTransition = {};