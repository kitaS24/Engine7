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