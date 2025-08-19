//
// Created by kitaS24 on 19.08.2025.
//

Vec3 IntToFloat3(Vec3I In){
    return {float(In.X),float(In.Y),float(In.Z)};
}
Vec3I FloatToInt3(Vec3 In){
    return {int(In.X),int(In.Y),int(In.Z)};
}

Vec3 Vec3Add(Vec3 A,Vec3 B){
    return {A.X+B.X,A.Y+B.Y,A.Z+B.Z};
}
Vec3 Vec3Subtract(Vec3 A,Vec3 B){
    return {A.X-B.X,A.Y-B.Y,A.Z-B.Z};
}
Vec3 Vec3Multiply(Vec3 A,Vec3 B){
    return {A.X*B.X,A.Y*B.Y,A.Z*B.Z};
}
Vec3 Vec3Divide(Vec3 A,Vec3 B){
    return {A.X/B.X,A.Y/B.Y,A.Z/B.Z};
}

Vec3I Vec3IAdd(Vec3I A,Vec3I B){
    return {A.X+B.X,A.Y+B.Y,A.Z+B.Z};
}
Vec3I Vec3ISubtract(Vec3I A,Vec3I B){
    return {A.X-B.X,A.Y-B.Y,A.Z-B.Z};
}
Vec3I Vec3IMultiply(Vec3I A,Vec3I B){
    return {A.X*B.X,A.Y*B.Y,A.Z*B.Z};
}
Vec3I Vec3IDivide(Vec3I A,Vec3I B){
    return {A.X/B.X,A.Y/B.Y,A.Z/B.Z};
}




float MagVec3(Vec3 in){
    return sqrt((in.X*in.X)+
                (in.Y*in.Y)+
                (in.Z*in.Z));
}
float MagVec3I(Vec3I in){
    return sqrt((float(in.X)*float(in.X))+
                (float(in.Y)*float(in.Y))+
                (float(in.Z)*float(in.Z)));
}

float Dist3F(Vec3 a,Vec3 b){
    return MagVec3({a.X-b.X,a.Y-b.Y,a.Z-b.Z});
}
float Dist3I(Vec3I a,Vec3I b){
    return MagVec3I({a.X-b.X,a.Y-b.Y,a.Z-b.Z});
}

Vec3 NormaliseVec3(Vec3 in){
    float dist = MagVec3(in);
    if(dist == 0){
        return {0,0,0};
    }
    return {in.X/dist,in.Y/dist,in.Z/dist};
}
Vec3 NormaliseVec3I(Vec3I in){
    float dist = MagVec3I(in);
    if(dist == 0){
        return {0,0,0};
    }
    return {float(in.X)/dist,float(in.Y)/dist,float(in.Z)/dist};
}

Vec3 Normalise2Vec3(Vec3 a,Vec3 b){
    return NormaliseVec3({a.X-b.X,a.Y-b.Y,a.Z-b.Z});
}

Vec3 rotatePoint(Vec3 point, Vec3 rotation) {
    float radX = rotation.X * Deg_To_Rad;
    float radY = rotation.Y * Deg_To_Rad;
    float radZ = rotation.Z * Deg_To_Rad;

    // X rot
    float cosX = cos(radX), sinX = sin(radX);
    float y1 = point.Y * cosX - point.Z * sinX;
    float z1 = point.Y * sinX + point.Z * cosX;

    // Y rot
    float cosY = cos(radY), sinY = sin(radY);
    float x2 = point.X * cosY + z1 * sinY;
    float z2 = -point.X * sinY + z1 * cosY;

    // Z rot
    float cosZ = cos(radZ), sinZ = sin(radZ);
    float x3 = x2 * cosZ - y1 * sinZ;
    float y3 = x2 * sinZ + y1 * cosZ;

    return {x3, y3, z2};
}

Vec3 rotatePointCam(Vec3 point, Vec3 rotation) {
    float radX = rotation.X * Deg_To_Rad;
    float radY = rotation.Y * Deg_To_Rad;
    float radZ = rotation.Z * Deg_To_Rad;

    // Z rotation
    float cosZ = cos(radZ), sinZ = sin(radZ);
    float x1 = point.X * cosZ - point.Y * sinZ;
    float y1 = point.X * sinZ + point.Y * cosZ;
    float z1 = point.Z;

    // Y rotation
    float cosY = cos(radY), sinY = sin(radY);
    float x2 = x1 * cosY + z1 * sinY;
    float y2 = y1;
    float z2 = -x1 * sinY + z1 * cosY;

    // X rotation
    float cosX = cos(radX), sinX = sin(radX);
    float x3 = x2;
    float y3 = y2 * cosX - z2 * sinX;
    float z3 = y2 * sinX + z2 * cosX;

    return {x3, y3, z3};
}

Vec3 multiplyMatrixVec3(const float matrix[16], const Vec3& vec) {
    Vec3 result;

    // Extend vec to homogeneous coordinates with w = 1
    float x = vec.X, y = vec.Y, z = vec.Z, w = 1.0f;

    result.X = matrix[0] * x + matrix[4] * y + matrix[8]  * z + matrix[12] * w;
    result.Y = matrix[1] * x + matrix[5] * y + matrix[9]  * z + matrix[13] * w;
    result.Z = matrix[2] * x + matrix[6] * y + matrix[10] * z + matrix[14] * w;

    return result;
}

Vec3 CrossProduct3F(Vec3 a, Vec3 b) {
    return {a.Y * b.Z - a.Z * b.Y,
            a.Z * b.X - a.X * b.Z,
            a.X * b.Y - a.Y * b.X};
}

float DotProduct3F(Vec3 a, Vec3 b) {
    return a.X*b.X + a.Y*b.Y + a.Z*b.Z;
}

Vec3 CapVec3(Vec3 In,float MaxDist){
    Vec3 Out = {};
    if(MagVec3(In) > MaxDist){
        Out = NormaliseVec3(In);
        return {Out.X*MaxDist,
                Out.Y*MaxDist,
                Out.Z*MaxDist};
    }
    return In;
}

float NormalizeAngle180(float InAng) {
    float angleDeg = fmodf(InAng + 180, 360);
    if (angleDeg < 0){
        angleDeg= angleDeg + 360;
    }
    return angleDeg - 180.0f;
}


unsigned int PcgHash(unsigned int input){
    //From :https://www.reedbeta.com/blog/hash-functions-for-gpu-rendering/  [13.8.2025]
    unsigned int state = input * 747796405u + 2891336453u;
    unsigned int word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    return (word >> 22u) ^ word;
}


float easeInOutQuart( float t ) {
    //From :https://github.com/nicolausYes/easing-functions/blob/master
    if( t < 0.5 ) {
        t *= t;
        return 8 * t * t;
    } else {
        t = (--t) * t;
        return 1 - 8 * t * t;
    }
}

float Interpolate(float A,float B,float I){
    return A+((B-A)*I);
}