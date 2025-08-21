//
// Created by kitaS24 on 21.08.2025.
//

float WorldRaycast(Vec3 Start,Vec3 End,Vec3 Size,float SampleRate,Brush *Brushes){
    Vec3 Dir = NormaliseVec3({End.X - Start.X,End.Y - Start.Y,End.Z - Start.Z});
    float D = MagVec3({End.X - Start.X,End.Y - Start.Y,End.Z - Start.Z});

    bool CollisionsUsed[Engine_Max_Brushes] = {};

    for (int i = 0; i < Engine_Max_Brushes; ++i) {
        CollisionsUsed[i] = AABBtoAABBSmart(Start,End,IntToFloat3((*(Brushes+i)).BoundingBox1),IntToFloat3((*(Brushes+i)).BoundingBox2));
    }

    for (int i = 0; i < D/SampleRate; ++i) {
        for (int j = 0; j < Engine_Max_Brushes; ++j) {
            if(CollisionsUsed[j]){
                if(CollisionInBrushArea(*(Brushes+j),{Start.X+(Dir.X*i*SampleRate),Start.Y+(Dir.Y*i*SampleRate),Start.Z+(Dir.Z*i*SampleRate)},Size)){
                    return i*SampleRate;
                }
            }
        }
    }
    return D;
}