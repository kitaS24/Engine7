//
// Created by kitaS24 on 25.08.2025.
//

// Copyright (c) 2025 kitaS24

void LoadMaterials(Material *Materials,std::string FileName) {
    int TextureId = 0;
    std::string materialNames[Engine_Max_Materials] = {};
    std::string V = "";
    IniRead Ini;

    Ini.SearchHeader(FileName, "material");//find [material]
    for (int i = 0; i < Engine_Max_Materials; ++i){
        //checking for "!" - error, else adding that to texture list
        V = Ini.ListHeaderContent();
        if (V.at(0) == '!') {
            break;
        }
        materialNames[TextureId] = V;
        TextureId = TextureId + 1;
    }


    for (int i = 0; i < TextureId; ++i) {
        //search for a header, getting base texture,data texture,shader,metal(bool),Specular RGB
        Ini.SearchHeader(FileName, materialNames[i]);

        (*(Materials + i + 1)).Texture = LoadBmpTexture(Ini.HeaderVar("base"), false, false);
        (*(Materials + i + 1)).TextureProperty = LoadBmpTexture(Ini.HeaderVar("data"), false, false);
        (*(Materials + i + 1)).Shader = OpenGlCreateShaderProgram(Ini.HeaderVar("vert"), Ini.HeaderVar("frag"));
        (*(Materials + i + 1)).Metal = bool(stoi(Ini.HeaderVar("metal")));
        (*(Materials + i + 1)).SpecColor.X= stof(Ini.HeaderVar("SpecR"));
        (*(Materials + i + 1)).SpecColor.Y= stof(Ini.HeaderVar("SpecG"));
        (*(Materials + i + 1)).SpecColor.Z= stof(Ini.HeaderVar("SpecB"));
        (*(Materials + i + 1)).Loaded = true;
        (*(Materials + i + 1)).TxProperty = true;
    }
}