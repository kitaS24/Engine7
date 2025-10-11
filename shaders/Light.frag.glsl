#version 120

// Copyright (c) 2025 kitaS24

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

void main() {

gl_FragColor = vec4(FloodPos.y-Pos.y,0,0,1);
}