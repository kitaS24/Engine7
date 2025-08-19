//
// Created by kitaS24 on 19.08.2025.
//

void AddLight(GpuLights *L,Vec3 Pos,Vec3 Color){
    int Index = 0;
    for (int i = 0; i < Engine_Max_Lights; ++i) {
        if(!(*L).enabled[i]){
            Index = i;
            break;
        }
    }
    (*L).Pos[Index*3+0] = Pos.X;
    (*L).Pos[Index*3+1] = Pos.Y;
    (*L).Pos[Index*3+2] = Pos.Z;

    (*L).Color[Index*3+0] = Color.X;
    (*L).Color[Index*3+1] = Color.Y;
    (*L).Color[Index*3+2] = Color.Z;

    (*L).enabled[Index] = true;
}