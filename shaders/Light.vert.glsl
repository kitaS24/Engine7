#version 120

// Copyright (c) 2025 kitaS24

varying vec4 fragColor;
varying vec2 texCoord;
varying vec3 Pos;
varying vec3 Normal;

uniform vec3 ChunkPos;

uniform vec3 FloodPos;
uniform vec3 FloodCol;
uniform vec3 FloodSize;
uniform vec3 FloodDir;

void main() {

    fragColor = gl_Color;
        texCoord = gl_MultiTexCoord0.xy;
        Pos = gl_MultiTexCoord1.xyz;
        //Pos = vec3(Pos.x,abs(Pos.y-FloodPos.y),Pos.z);
        float a = FloodPos.y-Pos.y;
        Normal = gl_MultiTexCoord2.xyz;

        gl_Position = gl_ModelViewProjectionMatrix*(gl_Vertex+vec4(FloodDir.x*a,0,FloodDir.z*a,0));

}