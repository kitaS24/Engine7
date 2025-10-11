//
// Created by kitaS24 on 08.09.2025.
//

// Copyright (c) 2025 kitaS24

BrushSide RenderSideRotate(BrushSide Br,Vec3 Transform[3],Vec3 Matrix[3]){
    BrushSide Out = Br;

    Vec3I Point = {};
    Vec3I PointAlt = {};

    for (int i = 0; i < Out.VertexN; ++i) {
        Point = Br.Vertex[i];
        Point = Vec3ISubtract(Point, FloatToInt3(Transform[1]));
        PointAlt.X =  int(float(Point.X)*Matrix[0].X + float(Point.Y)*Matrix[0].Y + float(Point.Z)*Matrix[0].Z);
        PointAlt.Y =  int(float(Point.X)*Matrix[1].X + float(Point.Y)*Matrix[1].Y + float(Point.Z)*Matrix[1].Z);
        PointAlt.Z =  int(float(Point.X)*Matrix[2].X + float(Point.Y)*Matrix[2].Y + float(Point.Z)*Matrix[2].Z);
        PointAlt = Vec3IAdd(PointAlt, FloatToInt3(Transform[1]));

        PointAlt =Vec3IAdd(PointAlt, FloatToInt3(Transform[0]));

        Out.Vertex[i] = PointAlt;
    }
    Vec3 PointF = {};
    Vec3 PointFAlt = {};
    PointF = Br.Normal;
    PointFAlt.X =  PointF.X*Matrix[0].X + PointF.Y*Matrix[0].Y + PointF.Z*Matrix[0].Z;
    PointFAlt.Y =  PointF.X*Matrix[1].X + PointF.Y*Matrix[1].Y + PointF.Z*Matrix[1].Z;
    PointFAlt.Z =  PointF.X*Matrix[2].X + PointF.Y*Matrix[2].Y + PointF.Z*Matrix[2].Z;
    Out.Normal = PointFAlt;

    PointF = Br.CollisionPos;
    PointF = Vec3Subtract(PointF, Transform[1]);
    PointFAlt.X =  PointF.X*Matrix[0].X + PointF.Y*Matrix[0].Y + PointF.Z*Matrix[0].Z;
    PointFAlt.Y =  PointF.X*Matrix[1].X + PointF.Y*Matrix[1].Y + PointF.Z*Matrix[1].Z;
    PointFAlt.Z =  PointF.X*Matrix[2].X + PointF.Y*Matrix[2].Y + PointF.Z*Matrix[2].Z;
    PointFAlt = Vec3Add(PointFAlt, Transform[1]);
    PointFAlt =Vec3Add(PointFAlt, Transform[0]);
    Out.CollisionPos = PointFAlt;
    return Out;
}


BrushSide CollisionSideRotate(BrushSide Br,Vec3 Transform[3],Vec3 Matrix[3]){
    BrushSide Out = Br;
/*
    Vec3I Point = {};
    Vec3I PointAlt = {};

    for (int i = 0; i < Out.VertexN; ++i) {
        Point = Br.Vertex[i];
        Point = Vec3ISubtract(Point, FloatToInt3(Transform[1]));
        PointAlt.X =  int(float(Point.X)*Matrix[0].X + float(Point.Y)*Matrix[0].Y + float(Point.Z)*Matrix[0].Z);
        PointAlt.Y =  int(float(Point.X)*Matrix[1].X + float(Point.Y)*Matrix[1].Y + float(Point.Z)*Matrix[1].Z);
        PointAlt.Z =  int(float(Point.X)*Matrix[2].X + float(Point.Y)*Matrix[2].Y + float(Point.Z)*Matrix[2].Z);
        PointAlt = Vec3IAdd(PointAlt, FloatToInt3(Transform[1]));

        PointAlt =Vec3IAdd(PointAlt, FloatToInt3(Transform[0]));

        Out.Vertex[i] = PointAlt;
    }
    */
    Vec3 PointF = {};
    Vec3 PointFAlt = {};
    PointF = Br.Normal;
    PointFAlt.X =  PointF.X*Matrix[0].X + PointF.Y*Matrix[0].Y + PointF.Z*Matrix[0].Z;
    PointFAlt.Y =  PointF.X*Matrix[1].X + PointF.Y*Matrix[1].Y + PointF.Z*Matrix[1].Z;
    PointFAlt.Z =  PointF.X*Matrix[2].X + PointF.Y*Matrix[2].Y + PointF.Z*Matrix[2].Z;
    Out.Normal = PointFAlt;

    PointF = Br.CollisionPos;
    PointF = Vec3Subtract(PointF, Transform[1]);
    PointFAlt.X =  PointF.X*Matrix[0].X + PointF.Y*Matrix[0].Y + PointF.Z*Matrix[0].Z;
    PointFAlt.Y =  PointF.X*Matrix[1].X + PointF.Y*Matrix[1].Y + PointF.Z*Matrix[1].Z;
    PointFAlt.Z =  PointF.X*Matrix[2].X + PointF.Y*Matrix[2].Y + PointF.Z*Matrix[2].Z;
    PointFAlt = Vec3Add(PointFAlt, Transform[1]);
    PointFAlt =Vec3Add(PointFAlt, Transform[0]);
    Out.CollisionPos = PointFAlt;
    return Out;
}


void RotateBrush(Brush &Br,Vec3 SetRot,Vec3 RotPoint){
    Br.Transformation[1] = RotPoint;
    Br.Transformation[2] = SetRot;
    Br.RotMatrix[0] = rotatePoint({1,0,0},SetRot);
    Br.RotMatrix[1] = rotatePoint({0,1,0},SetRot);
    Br.RotMatrix[2] = rotatePoint({0,0,1},SetRot);
    CreateBrushBoundingBox(Br);
}

void InitRotateMatrix(Brush &Br){
    for (int i = 0; i < 3; ++i) {
        Br.Transformation[i] = {0,0,0};
    }

    Br.RotMatrix[0] = {1,0,0};
    Br.RotMatrix[1] = {0,1,0};
    Br.RotMatrix[2] = {0,0,1};
}