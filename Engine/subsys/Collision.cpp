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

bool AABBtoAABB(Vec3 A1,Vec3 A2,Vec3 B1,Vec3 B2) {
    return (
            A1.X <= B2.X &&
            A2.X >= B1.X &&
            A1.Y <= B2.Y &&
            A2.Y >= B1.Y &&
            A1.Z <= B2.Z &&
            A2.Z >= B1.Z
    );
}

bool AABBtoAABBSmart(Vec3 A1,Vec3 A2,Vec3 B1,Vec3 B2){
    Vec3 A1s=A1;Vec3 A2s=A2;Vec3 B1s=B1;Vec3 B2s=B2;

    if(A2.X < A1.X){A1s.X=A2.X;A2s.X=A1.X;}
    if(A2.Y < A1.Y){A1s.Y=A2.Y;A2s.Y=A1.Y;}
    if(A2.Z < A1.Z){A1s.Z=A2.Z;A2s.Z=A1.Z;}

    if(B2.X < B1.X){B1s.X=B2.X;B2s.X=B1.X;}
    if(B2.Y < B1.Y){B1s.Y=B2.Y;B2s.Y=B1.Y;}
    if(B2.Z < B1.Z){B1s.Z=B2.Z;B2s.Z=B1.Z;}

    return AABBtoAABB(A1s,A2s,B1s,B2s);

}