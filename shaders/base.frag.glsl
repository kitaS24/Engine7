#version 120
uniform sampler2D tex;
uniform sampler2D PropTex;
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

vec3 CalculateLights(vec4 PropertyTx){
vec3 L = vec3(0.005,0.005,0.005);
    for(int i=0;i<LightN;i++){
        vec3 LightVel = normalize(LightPos[i]-Pos);
        float SurfaceDot = dot(Normal,LightVel);
        float IClDot = clamp(SurfaceDot,0,1);
        float D = distance(LightPos[i],Pos)/1000;
        vec3 R = reflect(-LightVel,Normal);
        //vec3 CL = LightCol[i]*IClDot;//*(pow(clamp(dot(R,(CamPos-Pos)),0,1),PropertyTx.y*500)*5+1);
        vec3 CL = LightCol[i]*IClDot*(pow(clamp(dot(R,normalize(CamPos-Pos)),0,1),PropertyTx.y*500)+mix(0.7,0.05,PropertyTx.y));
        L = L + (CL/(D*D*mix(1,0.1,PropertyTx.y)));
    }
    return L;
}

void main() {
vec4 Color = texture2D(tex,texCoord);
vec4 PropertyTx = vec4(0,0,0,0);
if(Property == 1){PropertyTx = texture2D(PropTex,texCoord);}
PropertyTx = vec4(PropertyTx.x*8+1,PropertyTx.y,PropertyTx.z*4,0);
//vec4 Color = vec4(Pos.x/10,Pos.y/10,Pos.z/10,1);
Color = Color * vec4(CalculateLights(PropertyTx)*PropertyTx.x+PropertyTx.z,1);
gl_FragColor = Color;
}