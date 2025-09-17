#version 120

/*
    Engine7 - a GoldSrc like engine
    Copyright (C) 2025  kitaS24

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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