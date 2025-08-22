//
// Created by kitaS24 on 18.08.2025.
//

std::vector<std::unique_ptr<Ent>> LevelEnt;
unsigned int DebugEntView = 0;
Brush LevelBrushes[Engine_Max_Brushes] = {};
Material Materials[Engine_Max_Materials] = {};
GpuLights Lights = {};

DISPLAY D = {};
Vec3 Cam[3] = {};

bool SaveOrLoadKeyPress = false;

MapKey UserKeyBind;