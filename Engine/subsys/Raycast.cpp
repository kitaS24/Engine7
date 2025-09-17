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

float WorldRaycast(Vec3 Start,Vec3 End,Vec3 Size,float SampleRate,Brush *Brushes){
    //sets Dist, Direction
    Vec3 Dir = NormaliseVec3({End.X - Start.X,End.Y - Start.Y,End.Z - Start.Z});
    float D = MagVec3({End.X - Start.X,End.Y - Start.Y,End.Z - Start.Z});

    bool CollisionsUsed[Engine_Max_Brushes] = {};

    //sets brushes that might collide
    for (int i = 0; i < Engine_Max_Brushes; ++i) {
        CollisionsUsed[i] = AABBtoAABBSmart(Start,End,IntToFloat3((*(Brushes+i)).BoundingBox1),IntToFloat3((*(Brushes+i)).BoundingBox2));
    }

    //checking every brush that can collide
    for (int i = 0; i < D/SampleRate; ++i) {
        for (int j = 0; j < Engine_Max_Brushes; ++j) {
            if(CollisionsUsed[j]){
                if(CollisionInBrushArea(*(Brushes+j),{Start.X+(Dir.X*i*SampleRate),Start.Y+(Dir.Y*i*SampleRate),Start.Z+(Dir.Z*i*SampleRate)},Size)){
                    return i*SampleRate;
                }
            }
        }
    }
    return D;
}