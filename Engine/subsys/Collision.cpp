//
// Created by kitaS24 on 20.08.2025.
//

bool CollisionBehindASide(BrushSide &S,Vec3 Point){
    //returns true if behind the plane
    Vec3 V = Vec3Subtract(Point,S.CollisionPos);
    return DotProduct3F(NormaliseVec3(V),S.Normal) <0;
}
bool CollisionInBrush(Brush &B,Vec3 Point){
    if(!B.Active){return false;}
    for (int i = 0; i < B.Planes; ++i) {
        if(!CollisionBehindASide(B.BrushPlane[i],Point)){
            return false;
        }
    }
    return true;
}
bool CollisionWorld(Brush *Brushes,unsigned int CheckBrushes,Vec3 Point){
    for (int i = 0; i < CheckBrushes; ++i) {
        if(CollisionInBrush(*(Brushes+i),Point)){
            return true;
        }
    }
    return false;
}

bool CollisionBehindASideArea(BrushSide &S,Vec3 Point,Vec3 HSize){
    //returns true if behind the plane
    Vec3 V = Vec3Subtract(Point, Vec3Add(S.CollisionPos, Vec3Multiply(S.Normal,HSize)));
    return DotProduct3F(NormaliseVec3(V),S.Normal) <0;
}
bool CollisionInBrushArea(Brush &B,Vec3 Point,Vec3 HSize){
    if(!B.Active){return false;}
    for (int i = 0; i < B.Planes; ++i) {
        if(!CollisionBehindASideArea(B.BrushPlane[i],Point,HSize)){
            return false;
        }
    }
    return true;
}
bool CollisionWorldArea(Brush *Brushes,unsigned int CheckBrushes,Vec3 Point,Vec3 HSize){
    for (int i = 0; i < CheckBrushes; ++i) {
        if(CollisionInBrushArea(*(Brushes+i),Point,HSize)){
            return true;
        }
    }
    return false;
}