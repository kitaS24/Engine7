#version 120

// Copyright (c) 2025 kitaS24

varying vec4 fragColor;
varying vec2 texCoord;
varying vec3 Pos;
varying vec3 Normal;

uniform vec3 ChunkPos;

void main() {

    fragColor = gl_Color;
    texCoord = gl_MultiTexCoord0.xy;
    Pos = gl_MultiTexCoord1.xyz;
    Normal = gl_MultiTexCoord2.xyz;

    gl_Position = gl_ModelViewProjectionMatrix * (gl_Vertex + vec4(0,0,0,0));

}