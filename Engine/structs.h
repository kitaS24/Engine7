//
// Created by kitaS24 on 18.08.2025.
//

#ifndef ENGINE7_STRUCTS_H
#define ENGINE7_STRUCTS_H


#define Engine_Brush_Planes 16

struct EntAction{
    int ActionType;
    unsigned int activator;
    unsigned int caller;
};

struct Vec2{
    float X;
    float Y;
};
struct Vec2I{
    int X;
    int Y;
};
struct Vec3{
    float X;
    float Y;
    float Z;
};
struct Vec3I{
    int X;
    int Y;
    int Z;
};
struct Vec4{
    float X;
    float Y;
    float Z;
    float A;
};
struct Vec4I{
    int X;
    int Y;
    int Z;
    int A;
};

struct BrushSide{
    bool Used;
    Vec3I Vertex[16];
    Vec2 Uvs[16];
    int VertexN;
    Vec3 Normal;
    Vec3 CollisionPos;
    unsigned int Material;
};

struct Brush{
    BrushSide BrushPlane[Engine_Brush_Planes];
    unsigned int Planes;
    int CollisionType;
    bool Active;
    Vec3 RotMatrix[3];
    Vec3 Transformation[3];//transform,rotationPoint,Rotation

    Vec3I BoundingBox1;
    Vec3I BoundingBox2;
};

struct BrushSave{
    unsigned int Planes;
    int CollisionType;
    bool Active;
    Vec3 Transformation[3];

    Vec3I BoundingBox1;
    Vec3I BoundingBox2;
};

struct Material{
    bool Loaded;
    bool TxProperty;
    bool Metal;
    Vec3 SpecColor;
    GLuint Texture;
    GLuint TextureProperty;//Metal|Roughness|LightI
    GLuint Shader;
};

struct GpuLights{
    float Pos[Engine_Max_Lights*3];
    float Color[Engine_Max_Lights*3];
    bool enabled[Engine_Max_Lights];

    Vec3 FloodPos;
    Vec3 FloodColor;
    Vec3 FloodSize;
    Vec3 FloodDir;
    GLuint Depth;
    bool FloodEnabled;
};

struct DISPLAY{
    int X;
    int Y;
    float FPS;
    double TPF;
    double lastT;
    GLFWwindow* window;
    int MX;
    int MY;
    bool Left;
    bool Right;
    bool Pressed;


};

struct MapTransition{
    std::string MapName = "";
    bool LoadMap = false;
    bool IsNewMap = false;
};

#endif //ENGINE7_STRUCTS_H
