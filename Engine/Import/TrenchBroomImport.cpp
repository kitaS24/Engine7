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

int TBSearchMaterial(std::string *MaterialName,int Textures,std::string TBMaterial){
    std::string TBMaterialClip = "";
    for (int i = 0; i < TBMaterial.length(); ++i) {
        if(TBMaterial.at(i) == '/' || TBMaterial.at(i) == '\\'){
            TBMaterialClip = "";
        }else{
            TBMaterialClip.append(1,TBMaterial.at(i));
        }
    }
    if(TBMaterialClip == "__TB_empty"){
        return 0;
    }
    //std::cout << TBMaterial<<"\n";
    for (int i = 0; i < Textures; ++i) {
        if(TBMaterialClip == *(MaterialName+i)){
            return i+2;
        }
    }
    return 1;
}

void LoadTBMap(Brush *Brushes,std::string MapName,std::string MaterialName,std::string SaveName,std::vector<std::unique_ptr<Ent>> &LevelEnt){
    // loads trench broom map from obj

    int TextureId = 0;
    std::string materialNames[Engine_Max_Materials] = {};
    std::string IniStr = "";
    IniRead Ini;

    Ini.SearchHeader(MaterialName, "material");
    for (int i = 0; i < Engine_Max_Materials; ++i){
        IniStr = Ini.ListHeaderContent();
        if (IniStr.at(0) == '!') {
            break;
        }
        materialNames[TextureId] = IniStr;
        TextureId = TextureId + 1;
    }

    unsigned int V=0;
    unsigned int TC=0;
    unsigned int N=0;
    int Brush = -1;
    int BrushSide = -1;
    GetTBMapInfo(V,TC,N,MapName);

    Vec3 * VertexDt;
    VertexDt = new Vec3 [V];
    Vec3 * TextureDt;
    TextureDt = new Vec3 [TC];
    Vec3 * NormalDt;
    NormalDt = new Vec3 [N];

    GetTBMapData(VertexDt,TextureDt,NormalDt,MapName,Engine_Map_Scale);


    TextSplit f;
    f.SetDivider(' ');
    TextSplit cf;
    cf.SetDivider('/');

    std::string ln;

    std::ifstream Read(MapName);


    while (getline (Read, ln)) {
        // Output the text from the file
        f.SetStr(ln);
        if(f.GetText(0) == "o"){
            if(Brush >=0){
                (*(Brushes+Brush)).Active = true;
                (*(Brushes+Brush)).Planes = BrushSide+1;
                //std::cout << (*(Brushes+Brush)).Planes<<"\n";
                CreateBrushBoundingBoxAll((*(Brushes+Brush)));
            }
            Brush = Brush+1;
            BrushSide =-1;
            //std::cout << "Brush:"<<Brush<<"\n";
        }
        if(BrushSide<Engine_Brush_Planes){
        if(f.GetText(0) == "usemtl"){
            BrushSide = BrushSide+1;

            (*(Brushes+Brush)).BrushPlane[BrushSide].Material =
                    TBSearchMaterial(materialNames,Engine_Max_Materials,f.GetText(1));
            //std::cout << "Texture:"<<(*(Brushes+Brush)).BrushPlane[BrushSide].Material<<"\n";
        }
        if(f.GetText(0) == "f") {
            for (int i = 0; i < 16 && (!f.GetTextOOB((i) * 2)); ++i) {
                cf.SetStr(f.GetText((i + 1) * 2));

                (*(Brushes + Brush)).BrushPlane[BrushSide].Vertex[i].X = VertexDt[stoi(cf.GetText(0)) - 1].X;
                (*(Brushes + Brush)).BrushPlane[BrushSide].Vertex[i].Y = VertexDt[stoi(cf.GetText(0)) - 1].Y;
                (*(Brushes + Brush)).BrushPlane[BrushSide].Vertex[i].Z = VertexDt[stoi(cf.GetText(0)) - 1].Z;

                (*(Brushes + Brush)).BrushPlane[BrushSide].Uvs[i].X = TextureDt[stoi(cf.GetText(1)) - 1].X;
                (*(Brushes + Brush)).BrushPlane[BrushSide].Uvs[i].Y = TextureDt[stoi(cf.GetText(1)) - 1].Y;


                (*(Brushes + Brush)).BrushPlane[BrushSide].VertexN = i + 1;
                //std::cout << "Data:"<<(*(Brushes+Brush)).BrushPlane[BrushSide].VertexN<<"\n";
            }
            (*(Brushes + Brush)).BrushPlane[BrushSide].Used = true;

            cf.SetStr(f.GetText(2));
            (*(Brushes + Brush)).BrushPlane[BrushSide].Normal.X = NormalDt[stoi(cf.GetText(2)) - 1].X;
            (*(Brushes + Brush)).BrushPlane[BrushSide].Normal.Y = NormalDt[stoi(cf.GetText(2)) - 1].Y;
            (*(Brushes + Brush)).BrushPlane[BrushSide].Normal.Z = NormalDt[stoi(cf.GetText(2)) - 1].Z;

            //(*(Brushes+Brush)).BrushPlane[BrushSide].Normal = {0,-1,0};



            (*(Brushes + Brush)).BrushPlane[BrushSide].CollisionPos.X = (*(Brushes +Brush)).BrushPlane[BrushSide].Vertex[0].X;
            (*(Brushes + Brush)).BrushPlane[BrushSide].CollisionPos.Y = (*(Brushes +Brush)).BrushPlane[BrushSide].Vertex[0].Y;
            (*(Brushes + Brush)).BrushPlane[BrushSide].CollisionPos.Z = (*(Brushes +Brush)).BrushPlane[BrushSide].Vertex[0].Z;
        }
            /*
            std::cout <<"X:"<<(*(Brushes+Brush)).BrushPlane[BrushSide].CollisionPos.X<<
                      "|Y:"<<(*(Brushes+Brush)).BrushPlane[BrushSide].CollisionPos.Y<<
                      "|Z:"<<(*(Brushes+Brush)).BrushPlane[BrushSide].CollisionPos.Z<<"\n";*/


        }
    }
    if(Brush >=0){
        (*(Brushes+Brush)).Active = true;
        (*(Brushes+Brush)).Planes = BrushSide+1;
        if((*(Brushes+Brush)).Planes >Engine_Brush_Planes){
            (*(Brushes+Brush)).Planes =Engine_Brush_Planes;
        }
       //std::cout << (*(Brushes+Brush)).Planes<<"\n";
        CreateBrushBoundingBoxAll((*(Brushes+Brush)));
    }


    Read.close();


    delete[] VertexDt;
    delete[] TextureDt;
    delete[] NormalDt;

    //EngineSave(LevelEnt,Brushes,SaveName);

    std::cout << "V:"<<V<<"\n";
    std::cout << "TC:"<<TC<<"\n";
    std::cout << "N:"<<N<<"\n";
}


void ImportEnts(std::string MapName,std::vector<std::unique_ptr<Ent>> &LevelEnt){
    // form map file

    std::string ln;
    std::string lnC;

    std::ifstream Read(MapName);

    TextSplit f;
    f.SetDivider(' ');
    std::string Parameters[3] = {};
    bool EntWrite = false;
    while (getline (Read, ln)) {
        if(ln.at(0) == '"'){
            //try to read property
            //the worst way to read any file

            lnC = "";
            for (int i = 0; i < ln.length(); ++i) {
                if(ln.at(i) != '"'){
                    lnC.append(1,ln.at(i));
                }
            }


            f.SetStr(lnC);

            int v = 0;

            for (int i = 0; i < 3; ++i) {
                Parameters[i] = "";
            }
            for (int i = 0; i < lnC.length(); ++i) {
                if(lnC.at(i) == ' ' && v ==0){
                    v++;
                }else{
                    Parameters[v].append(1,lnC.at(i));
                }
            }

            for (int i = 0; i < Parameters[0].length(); ++i) {
                //to lower case
                if(Parameters[0].at(i) >='A' && Parameters[0].at(i)<='Z'){
                    Parameters[2].append(1,Parameters[0].at(i) + ('a'-'A'));
                }else{
                    Parameters[2].append(1,Parameters[0].at(i));
                }
            }

            if(EntWrite) {
                if (LevelEnt[LevelEnt.size() - 1]) {
                    LevelEnt[LevelEnt.size() - 1]->SetVar(Parameters[2], Parameters[1]);
                }
            }else{
                if(Parameters[2] == "classname") {
                    if (EntCreate(Parameters[1], LevelEnt)) {
                        EntWrite = true;
                    }
                }
            }

            //std::cout << "N:"<<Parameters[2]<<"\n";
            //std::cout << "NO:"<<Parameters[0]<<"\n";
            //std::cout << "V:"<<Parameters[1]<<"\n";
        }

        if(ln.at(0) == '}'){
            EntWrite = false;
        }
    }
    Read.close();
}