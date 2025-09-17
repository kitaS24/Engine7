//
// Created by kitaS24 on 08.09.2025.
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