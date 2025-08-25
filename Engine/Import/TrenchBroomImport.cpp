//
// Created by kitaS24 on 24.08.2025.
//


void GetTBMapInfo(unsigned int &V,unsigned int &TC,unsigned int &N,std::string File){

    unsigned int vert = 0;
    TextSplit f;
    f.SetDivider(' ');

    std::string ln;
    // Read from the text file
    std::ifstream Read(File);

    // Use a while loop together with the getline() function to read the file line by line
    while (getline (Read, ln)) {
        // Output the text from the file
        f.SetStr(ln);
        if(f.GetText(0) == "v"){
            V = V+1;
        }
        if(f.GetText(0) == "vt"){
            TC = TC+1;
        }
        if(f.GetText(0) == "vn"){
            N = N+1;
        }
    }

    // Close the file
    Read.close();

}

void GetTBMapData(Vec3 *V,Vec3 *TC,Vec3 *N,std::string File,float Scale){

    unsigned int IndexV=0;
    unsigned int IndexTC=0;
    unsigned int IndexN=0;

    TextSplit f;
    f.SetDivider(' ');

    std::string ln;

    std::ifstream Read(File);


    while (getline (Read, ln)) {

        f.SetStr(ln);
        if(f.GetText(0) == "v"){
            *(V +IndexV )={stof(f.GetText(1))*Scale,stof(f.GetText(2))*Scale,stof(f.GetText(3))*Scale};
            IndexV = IndexV+1;
        }
        if(f.GetText(0) == "vt"){
            *(TC+IndexTC)={stof(f.GetText(1)),stof(f.GetText(2)),0};//UV ONLY
            IndexTC = IndexTC+1;
        }
        if(f.GetText(0) == "vn"){
            *(N +IndexN )={stof(f.GetText(1)),stof(f.GetText(2)),stof(f.GetText(3))};
            IndexN = IndexN+1;
        }
    }


    Read.close();

}

void LoadTBMap(Brush *Brushes){
    // loads trench broom map from obj
    unsigned int V=0;
    unsigned int TC=0;
    unsigned int N=0;
    int Brush = -1;
    int BrushSide = -1;
    GetTBMapInfo(V,TC,N,"test.obj");

    Vec3 * VertexDt;
    VertexDt = new Vec3 [V];
    Vec3 * TextureDt;
    TextureDt = new Vec3 [TC];
    Vec3 * NormalDt;
    NormalDt = new Vec3 [N];

    GetTBMapData(VertexDt,TextureDt,NormalDt,"test.obj",25.4);


    TextSplit f;
    f.SetDivider(' ');
    TextSplit cf;
    cf.SetDivider('/');

    std::string ln;

    std::ifstream Read("test.obj");


    while (getline (Read, ln)) {
        // Output the text from the file
        f.SetStr(ln);
        if(f.GetText(0) == "o"){
            if(Brush >=0){
                (*(Brushes+Brush)).Active = true;
                (*(Brushes+Brush)).Planes = BrushSide+1;
                std::cout << (*(Brushes+Brush)).Planes<<"\n";
                CreateBrushBoundingBoxAll((*(Brushes+Brush)));
            }
            Brush = Brush+1;
            BrushSide =-1;
            std::cout << "Brush:"<<Brush<<"\n";
        }
        if(f.GetText(0) == "usemtl"){
            BrushSide = BrushSide+1;

            (*(Brushes+Brush)).BrushPlane[BrushSide].Material = 2;
            //std::cout << "Texture:"<<f.GetText(1)<<"\n";
        }
        if(f.GetText(0) == "f"){
            for (int i = 0;i<16 && (!f.GetTextOOB((i)*2));++i){
                cf.SetStr(f.GetText((i+1)*2));

                (*(Brushes+Brush)).BrushPlane[BrushSide].Vertex[i].X = VertexDt[stoi(cf.GetText(0))-1].X;
                (*(Brushes+Brush)).BrushPlane[BrushSide].Vertex[i].Y = VertexDt[stoi(cf.GetText(0))-1].Y-1000;
                (*(Brushes+Brush)).BrushPlane[BrushSide].Vertex[i].Z = VertexDt[stoi(cf.GetText(0))-1].Z;

                (*(Brushes+Brush)).BrushPlane[BrushSide].Uvs[i].X = TextureDt[stoi(cf.GetText(1))-1].X;
                (*(Brushes+Brush)).BrushPlane[BrushSide].Uvs[i].Y = TextureDt[stoi(cf.GetText(1))-1].Y;


                (*(Brushes+Brush)).BrushPlane[BrushSide].VertexN = i+1;
                //std::cout << "Data:"<<(*(Brushes+Brush)).BrushPlane[BrushSide].VertexN<<"\n";
            }
            (*(Brushes+Brush)).BrushPlane[BrushSide].Used = true;

            cf.SetStr(f.GetText(2));
            (*(Brushes+Brush)).BrushPlane[BrushSide].Normal.X = NormalDt[stoi(cf.GetText(2))-1].X;
            (*(Brushes+Brush)).BrushPlane[BrushSide].Normal.Y = NormalDt[stoi(cf.GetText(2))-1].Y;
            (*(Brushes+Brush)).BrushPlane[BrushSide].Normal.Z = NormalDt[stoi(cf.GetText(2))-1].Z;

            //(*(Brushes+Brush)).BrushPlane[BrushSide].Normal = {0,-1,0};



            (*(Brushes+Brush)).BrushPlane[BrushSide].CollisionPos.X = (*(Brushes+Brush)).BrushPlane[BrushSide].Vertex[0].X;
            (*(Brushes+Brush)).BrushPlane[BrushSide].CollisionPos.Y = (*(Brushes+Brush)).BrushPlane[BrushSide].Vertex[0].Y;
            (*(Brushes+Brush)).BrushPlane[BrushSide].CollisionPos.Z = (*(Brushes+Brush)).BrushPlane[BrushSide].Vertex[0].Z;
            /*
            std::cout <<"X:"<<(*(Brushes+Brush)).BrushPlane[BrushSide].CollisionPos.X<<
                      "|Y:"<<(*(Brushes+Brush)).BrushPlane[BrushSide].CollisionPos.Y<<
                      "|Z:"<<(*(Brushes+Brush)).BrushPlane[BrushSide].CollisionPos.Z<<"\n";*/


        }
    }
    if(Brush >=0){
        (*(Brushes+Brush)).Active = true;
        (*(Brushes+Brush)).Planes = BrushSide+1;
        std::cout << (*(Brushes+Brush)).Planes<<"\n";
        CreateBrushBoundingBoxAll((*(Brushes+Brush)));
    }


    Read.close();


    delete[] VertexDt;
    delete[] TextureDt;
    delete[] NormalDt;

    std::cout << "V:"<<V<<"\n";
    std::cout << "TC:"<<TC<<"\n";
    std::cout << "N:"<<N<<"\n";
}