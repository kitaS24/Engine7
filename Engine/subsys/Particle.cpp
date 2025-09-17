//
// Created by kitaS24 on 21.08.2025.
//

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

void RenderParticle(Vec3 *Pos,unsigned int RenderParticles,Vec3 Rot,Vec2 Size,Material *Material,GpuLights *L,unsigned int LN,Vec3 CamPos,Vec4 Color){
    glEnable(GL_TEXTURE_2D);
    //sets shader, texture
    if(!(*Material).Loaded){
        glUseProgram(NULL);
        glColor3ub(255,0,0);
    }else {
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, (*Material).Texture);
        if((*Material).TxProperty) {
            glActiveTexture(GL_TEXTURE1);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, (*Material).TextureProperty);
        }
        //sets data
        glUseProgram((*Material).Shader);
        glUniform3fv(glGetUniformLocation((*Material).Shader, "LightPos"), LN,(*L).Pos);
        glUniform3fv(glGetUniformLocation((*Material).Shader, "LightCol"), LN,(*L).Color);

        glUniform3fv(glGetUniformLocation((*Material).Shader, "LightDir"), ClampInt(LN,0,Engine_MaxSpotLights-1),(*L).Dir);
        glUniform3fv(glGetUniformLocation((*Material).Shader, "LightDt"), ClampInt(LN,0,Engine_MaxSpotLights-1),(*L).Data);

        glUniform1i(glGetUniformLocation((*Material).Shader, "LightN"), LN);
        glUniform1i(glGetUniformLocation((*Material).Shader, "Property"), (*Material).TxProperty);
        glUniform1i(glGetUniformLocation((*Material).Shader, "PropTex"), 1);
        glUniform3f(glGetUniformLocation((*Material).Shader, "CamPos"), CamPos.X,CamPos.Y,CamPos.Z);

    }

    Vec3 PPos[4] = {
            rotatePoint({-Size.X,-Size.Y,0},Rot),
            rotatePoint({Size.X,-Size.Y,0},Rot),
            rotatePoint({Size.X,Size.Y,0},Rot),
            rotatePoint({-Size.X,Size.Y,0},Rot),
    };
    Vec3 Normal = rotatePoint({0,0,-1},Rot);

    glBegin(GL_QUADS);
    glColor4ub(Color.X,Color.Y,Color.Z,Color.A);
    glMultiTexCoord3f(GL_TEXTURE2,Normal.X,Normal.Y,Normal.Z);

    //render all particles
    for (int i = 0; i < RenderParticles; ++i) {
        glMultiTexCoord2f(GL_TEXTURE0, 0, 0);
        glMultiTexCoord3f(GL_TEXTURE1, (*(Pos+i)).X + PPos[0].X, (*(Pos+i)).Y + PPos[0].Y, (*(Pos+i)).Z + PPos[0].Z);
        glVertex3f((*(Pos+i)).X + PPos[0].X, (*(Pos+i)).Y + PPos[0].Y, (*(Pos+i)).Z + PPos[0].Z);
        glMultiTexCoord2f(GL_TEXTURE0, 1, 0);
        glMultiTexCoord3f(GL_TEXTURE1, (*(Pos+i)).X + PPos[1].X, (*(Pos+i)).Y + PPos[1].Y, (*(Pos+i)).Z + PPos[1].Z);
        glVertex3f((*(Pos+i)).X + PPos[1].X, (*(Pos+i)).Y + PPos[1].Y, (*(Pos+i)).Z + PPos[1].Z);
        glMultiTexCoord2f(GL_TEXTURE0, 1, 1);
        glMultiTexCoord3f(GL_TEXTURE1, (*(Pos+i)).X + PPos[2].X, (*(Pos+i)).Y + PPos[2].Y, (*(Pos+i)).Z + PPos[2].Z);
        glVertex3f((*(Pos+i)).X + PPos[2].X, (*(Pos+i)).Y + PPos[2].Y, (*(Pos+i)).Z + PPos[2].Z);
        glMultiTexCoord2f(GL_TEXTURE0, 0, 1);
        glMultiTexCoord3f(GL_TEXTURE1, (*(Pos+i)).X + PPos[3].X, (*(Pos+i)).Y + PPos[3].Y, (*(Pos+i)).Z + PPos[3].Z);
        glVertex3f((*(Pos+i)).X + PPos[3].X, (*(Pos+i)).Y + PPos[3].Y, (*(Pos+i)).Z + PPos[3].Z);
    }
    //end
    glEnd();
    glActiveTexture(GL_TEXTURE1);
    glDisable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glDisable(GL_TEXTURE_2D);
}


void ShadowRenderParticle(Vec3 *Pos,unsigned int RenderParticles,Vec3 Rot,Vec2 Size,GLuint Shader,Vec3 LightPos,Vec3 LightSize,Vec3 LightDir){
    //sets a shader
    glUseProgram(Shader);
    //sets Flood data
    glUniform3f(glGetUniformLocation(Shader, "FloodPos"), LightPos.X, LightPos.Y, LightPos.Z);
    glUniform3f(glGetUniformLocation(Shader, "FloodSize"), LightSize.X, LightSize.Y, LightSize.Z);
    glUniform3f(glGetUniformLocation(Shader, "FloodDir"), LightDir.X, LightDir.Y, LightDir.Z);

    Vec3 PPos[4] = {
            rotatePoint({-Size.X,-Size.Y,0},Rot),
            rotatePoint({Size.X,-Size.Y,0},Rot),
            rotatePoint({Size.X,Size.Y,0},Rot),
            rotatePoint({-Size.X,Size.Y,0},Rot),
    };
    Vec3 Normal = rotatePoint({0,0,-1},Rot);

    // same, rendering particles
    glBegin(GL_QUADS);
    glMultiTexCoord3f(GL_TEXTURE2,Normal.X,Normal.Y,Normal.Z);
    glColor3ub(255,255,255);
    for (int i = 0; i < RenderParticles; ++i) {
        glMultiTexCoord2f(GL_TEXTURE0, 0, 0);
        glMultiTexCoord3f(GL_TEXTURE1, (*(Pos+i)).X + PPos[0].X, (*(Pos+i)).Y + PPos[0].Y, (*(Pos+i)).Z + PPos[0].Z);
        glVertex3f((*(Pos+i)).X + PPos[0].X, (*(Pos+i)).Y + PPos[0].Y, (*(Pos+i)).Z + PPos[0].Z);
        glMultiTexCoord2f(GL_TEXTURE0, 1, 0);
        glMultiTexCoord3f(GL_TEXTURE1, (*(Pos+i)).X + PPos[1].X, (*(Pos+i)).Y + PPos[1].Y, (*(Pos+i)).Z + PPos[1].Z);
        glVertex3f((*(Pos+i)).X + PPos[1].X, (*(Pos+i)).Y + PPos[1].Y, (*(Pos+i)).Z + PPos[1].Z);
        glMultiTexCoord2f(GL_TEXTURE0, 1, 1);
        glMultiTexCoord3f(GL_TEXTURE1, (*(Pos+i)).X + PPos[2].X, (*(Pos+i)).Y + PPos[2].Y, (*(Pos+i)).Z + PPos[2].Z);
        glVertex3f((*(Pos+i)).X + PPos[2].X, (*(Pos+i)).Y + PPos[2].Y, (*(Pos+i)).Z + PPos[2].Z);
        glMultiTexCoord2f(GL_TEXTURE0, 0, 1);
        glMultiTexCoord3f(GL_TEXTURE1, (*(Pos+i)).X + PPos[3].X, (*(Pos+i)).Y + PPos[3].Y, (*(Pos+i)).Z + PPos[3].Z);
        glVertex3f((*(Pos+i)).X + PPos[3].X, (*(Pos+i)).Y + PPos[3].Y, (*(Pos+i)).Z + PPos[3].Z);
    }
    //end
    glEnd();
}