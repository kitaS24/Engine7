//
// Created by kitaS24 on 21.08.2025.
//

void CreateBrushBoundingBox(Brush &Br){
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
    CreateBrushBoundingBox(Br);
    CreateBrushBoundingBoxNormals(Br);
}