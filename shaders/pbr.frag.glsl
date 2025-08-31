#version 120
uniform sampler2D tex;
uniform sampler2D PropTex;
uniform sampler2D FloodD;
//uniform sampler2D BlockInfo;
varying vec4 fragColor;
varying vec2 texCoord;
varying vec3 Pos;
varying vec3 Normal;

//In
uniform vec3 LightPos[512];
uniform vec3 LightCol[512];
uniform int LightN;
uniform int Property;//1 to read property tx
uniform vec3 CamPos;
//Material
uniform vec3 SpecColor;
//FloodLight
uniform vec3 FloodPos;
uniform vec3 FloodCol;
uniform vec3 FloodSize;
uniform vec3 FloodDir;
uniform int FloodN;


float GGX(vec3 LightVec,vec3 CamVec,float a){
vec3 halfVec = normalize(LightVec+CamVec);
float a2 = a*a*a*a;
float divP2 = ((dot(Normal,halfVec)*dot(Normal,halfVec))*(a2-1)+1);
divP2 = divP2*divP2;
return (a2)/(3.14159265*divP2);
}

float geomSmithPrivate(vec3 CamVec,float k){
// modif SchlickGGX
float dt = dot(Normal,CamVec);
return (dt)/(dt*(1-k)+k);
}
float geomSmith(vec3 CamVec,vec3 LightVec,float a){
float k = ((a+1)*(a+1))/8;
return geomSmithPrivate(CamVec,k)*geomSmithPrivate(LightVec,k);
}
vec3 SchlickApprox(vec3 CamVec,vec3 LightVec,vec3 F){
vec3 halfVec = normalize(LightVec+CamVec);
return F + (1-F)*pow(clamp((1-dot(CamVec,halfVec)),0.0,1.0),5);
}

vec3 SpecularBRDF(float kS,vec3 Color,float Roughness,vec3 FCol,vec3 LPos){
vec3 LightVec = normalize(LPos-Pos);
vec3 CamVec = normalize(CamPos-Pos);
float D = GGX(LightVec,CamVec,Roughness);
float G = geomSmith(CamVec,LightVec,Roughness);
vec3 F = SchlickApprox(CamVec,LightVec,FCol);


return (D*G*F)/(1*dot(Normal,LightVec)*dot(Normal,CamVec));
}

vec3 DiffuseBRDF(float kD,vec3 Color){
return kD*Color/3.14159265;
}

vec2 FloodLightCollision(vec3 FPos,vec3 FSize,vec3 FVec,vec3 Point){
//returns UV
float Ydist = FPos.y - Point.y;
vec3 FPosNew = FPos+vec3(FVec.x*-Ydist,0,FVec.z*-Ydist);
vec2 p = vec2(Point.x-FPosNew.x,Point.z-FPosNew.z);
return p/vec2(FSize.x,FSize.z)/2;
}

float SampleNearestDepth(vec3 FPos,vec2 UV){
float A = 0;
float D = 1.0f/4096;
float V = -((1-clamp(dot(Normal,vec3(0,1,0)),0,1))*20);
/*
float Dt[4];
if(-(texture2D(FloodD,vec2(UV.x,UV.y))).x+FPos.y<= Pos.y){Dt[0] = 1;}else{Dt[0] = 0;}
if(-(texture2D(FloodD,vec2(UV.x+D,UV.y))).x+FPos.y<= Pos.y){Dt[1] = 1;}else{Dt[1] = 0;}
if(-(texture2D(FloodD,vec2(UV.x+D,UV.y+D))).x+FPos.y<= Pos.y){Dt[2] = 1;}else{Dt[2] = 0;}
if(-(texture2D(FloodD,vec2(UV.x,UV.y+D))).x+FPos.y<= Pos.y){Dt[3] = 1;}else{Dt[3] = 0;}

float x = (UV.x*64.0f)-floor(UV.x*64.0f);
float y = (UV.y*64.0f)-floor(UV.y*64.0f);

return mix(mix(Dt[0],Dt[1],x),mix(Dt[3],Dt[2],x),y);
*/

if(-(texture2D(FloodD,UV)).x+FPos.y+V<= Pos.y){A = A +1;}

//return A;

if(-(texture2D(FloodD,vec2(UV.x+D,UV.y))).x+FPos.y+V<= Pos.y){A = A +1;}
if(-(texture2D(FloodD,vec2(UV.x-D,UV.y))).x+FPos.y+V<= Pos.y){A = A +1;}
if(-(texture2D(FloodD,vec2(UV.x,UV.y+D))).x+FPos.y+V<= Pos.y){A = A +1;}
if(-(texture2D(FloodD,vec2(UV.x,UV.y-D))).x+FPos.y+V<= Pos.y){A = A +1;}

if(-(texture2D(FloodD,vec2(UV.x-D,UV.y-D))).x+FPos.y+V<= Pos.y){A = A +1;}
if(-(texture2D(FloodD,vec2(UV.x+D,UV.y-D))).x+FPos.y+V<= Pos.y){A = A +1;}
if(-(texture2D(FloodD,vec2(UV.x+D,UV.y+D))).x+FPos.y+V<= Pos.y){A = A +1;}
if(-(texture2D(FloodD,vec2(UV.x-D,UV.y+D))).x+FPos.y+V<= Pos.y){A = A +1;}
/*
if(-(texture2D(FloodD,vec2(UV.x+D+D,UV.y))).x+FPos.y<= Pos.y){A = A +1;}
if(-(texture2D(FloodD,vec2(UV.x-D-D,UV.y))).x+FPos.y<= Pos.y){A = A +1;}
if(-(texture2D(FloodD,vec2(UV.x,UV.y+D+D))).x+FPos.y<= Pos.y){A = A +1;}
if(-(texture2D(FloodD,vec2(UV.x,UV.y-D-D))).x+FPos.y<= Pos.y){A = A +1;}

if(-(texture2D(FloodD,vec2(UV.x-D-D,UV.y-D-D))).x+FPos.y<= Pos.y){A = A +1;}
if(-(texture2D(FloodD,vec2(UV.x+D+D,UV.y-D-D))).x+FPos.y<= Pos.y){A = A +1;}
if(-(texture2D(FloodD,vec2(UV.x+D+D,UV.y+D+D))).x+FPos.y<= Pos.y){A = A +1;}
if(-(texture2D(FloodD,vec2(UV.x-D-D,UV.y+D+D))).x+FPos.y<= Pos.y){A = A +1;}
*/
float R = A/9;
if(R <0.05){R = 0.05;}
return R;
}

vec3 CalculateLights(float k,vec3 F,vec3 Color,float Roughness){
vec3 C = Color*vec3(0.005,0.005,0.005);
    for(int i=0;i<LightN;i++){
        vec3 LightVec = normalize(LightPos[i]-Pos);
        float SurfaceDot = dot(Normal,LightVec);
        float IClDot = clamp(SurfaceDot,0,1);
        float D = distance(LightPos[i],Pos)/1000;
        vec3 LightI = LightCol[i]/(D*D);
        vec3 CL = (DiffuseBRDF(k,Color)+SpecularBRDF(1-k,Color,Roughness,F,LightPos[i]))*LightI*IClDot;
        C = C + CL;
    }
    //flood light
    //return Color/5000;
    if(FloodN == 1){

    vec2 FloodUV = FloodLightCollision(FloodPos,FloodSize,FloodDir,Pos);
    FloodUV = FloodUV +0.5;
    vec3 LightVec = normalize(FloodPos-Pos);
    //vec3 LightVec = normalize(vec3(FloodDir.x,FloodPos.y-Pos.y,FloodDir.z));
    float SurfaceDot = dot(Normal,LightVec);
    float IClDot =clamp(SurfaceDot,0,1);
    //return vec3(((((texture2D(FloodD,vec2(FloodUV.x,FloodUV.y))).x)+FloodPos.y)-Pos.y)/10000+5000,0,0);
    //return vec3((FloodPos.y-Pos.y-(texture2D(FloodD,vec2(FloodUV.x,FloodUV.y))).x)/10000,0,0);

    //return FloodCol[i];
    if(IClDot >0){
    if(FloodUV.x >0 && FloodUV.x <=1 && FloodUV.y >0 && FloodUV.y <=1){

                float D = distance(FloodPos,Pos)/1000;
                vec3 LightI = FloodCol/(D*D*0.25);
                //LightI = vec3(FloodUV,0);
                vec3 CL = (DiffuseBRDF(k,Color)+SpecularBRDF(1-k,Color,Roughness,F,FloodPos))*LightI*IClDot*
               SampleNearestDepth(FloodPos,FloodUV);
                C = C + CL;
    }else{

                    float D = distance(FloodPos,Pos)/1000;
                                    vec3 LightI = FloodCol/(D*D*0.25);
                                    //LightI = vec3(FloodUV,0);
                                    vec3 CL = (DiffuseBRDF(k,Color)+SpecularBRDF(1-k,Color,Roughness,F,FloodPos))*LightI*IClDot*
                                   0.05;
                                    C = C + CL;
    }
    }
    }
    return C;
}

void main() {
vec4 Color = texture2D(tex,texCoord);
vec4 PropertyTx = vec4(0,0.6,0,0);
if(Property == 1){PropertyTx = texture2D(PropTex,texCoord);}
PropertyTx = vec4(PropertyTx.x,PropertyTx.y,PropertyTx.z*4,0);

//property X = Metal | property Y = Roughness
Color = vec4(CalculateLights(PropertyTx.x,SpecColor,Color.xyz,PropertyTx.y),1);
//Color = vec4((texture2D(FloodD,texCoord)).x/2000,0,0,1);
gl_FragColor = fragColor*Color;
}