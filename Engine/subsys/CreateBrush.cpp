//
// Created by kitaS24 on 21.08.2025.
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

void CreateBrushBoundingBox(Brush &Br){
    //creates bounding box by getting every vertex
    Br.BoundingBox1 = Br.BrushPlane[0].Vertex[0];
    Br.BoundingBox2 = Br.BrushPlane[0].Vertex[0];
    for (int i = 0; i < Br.Planes; ++i) {
        for (int j = 0; j < Br.BrushPlane[i].VertexN; ++j) {
            if(Br.BoundingBox1.X > Br.BrushPlane[i].Vertex[j].X){
                Br.BoundingBox1.X = Br.BrushPlane[i].Vertex[j].X;
            }
            if(Br.BoundingBox1.Y > Br.BrushPlane[i].Vertex[j].Y){
                Br.BoundingBox1.Y = Br.BrushPlane[i].Vertex[j].Y;
            }
            if(Br.BoundingBox1.Z > Br.BrushPlane[i].Vertex[j].Z){
                Br.BoundingBox1.Z = Br.BrushPlane[i].Vertex[j].Z;
            }
            //
            if(Br.BoundingBox2.X < Br.BrushPlane[i].Vertex[j].X){
                Br.BoundingBox2.X = Br.BrushPlane[i].Vertex[j].X;
            }
            if(Br.BoundingBox2.Y < Br.BrushPlane[i].Vertex[j].Y){
                Br.BoundingBox2.Y = Br.BrushPlane[i].Vertex[j].Y;
            }
            if(Br.BoundingBox2.Z < Br.BrushPlane[i].Vertex[j].Z){
                Br.BoundingBox2.Z = Br.BrushPlane[i].Vertex[j].Z;
            }
        }
    }
}

void CreateBrushBoundingBoxNormals(Brush &Br){
    //creates bounding box by getting every CollisionPos
    for (int i = 0; i < Br.Planes; ++i) {
            if(Br.BoundingBox1.X > Br.BrushPlane[i].CollisionPos.X){
                Br.BoundingBox1.X = Br.BrushPlane[i].CollisionPos.X;
            }
            if(Br.BoundingBox1.Y > Br.BrushPlane[i].CollisionPos.Y){
                Br.BoundingBox1.Y = Br.BrushPlane[i].CollisionPos.Y;
            }
            if(Br.BoundingBox1.Z > Br.BrushPlane[i].CollisionPos.Z){
                Br.BoundingBox1.Z = Br.BrushPlane[i].CollisionPos.Z;
            }
            //
            if(Br.BoundingBox2.X < Br.BrushPlane[i].CollisionPos.X){
                Br.BoundingBox2.X = Br.BrushPlane[i].CollisionPos.X;
            }
            if(Br.BoundingBox2.Y < Br.BrushPlane[i].CollisionPos.Y){
                Br.BoundingBox2.Y = Br.BrushPlane[i].CollisionPos.Y;
            }
            if(Br.BoundingBox2.Z < Br.BrushPlane[i].CollisionPos.Z){
                Br.BoundingBox2.Z = Br.BrushPlane[i].CollisionPos.Z;
            }
    }
}
void CreateBrushBoundingBoxAll(Brush &Br){
    //does both
    CreateBrushBoundingBox(Br);
    CreateBrushBoundingBoxNormals(Br);
}