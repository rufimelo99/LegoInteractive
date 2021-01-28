#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "vector4d.h"
#include "matrix4d.h"

using namespace Vectors;
using namespace Matrices;

namespace Quaternions{

    struct quaternion{
        float t, x, y, z;
        float openglMatrixValues[16];

        quaternion(); 
        quaternion(float theta, const vector4D& axis); 
        quaternion(const quaternion& q); 
        quaternion operator=(const quaternion& q);
        quaternion operator*(const quaternion& q);
        static void toAngleAxis(const quaternion& q, float& theta, vector4D& axis);
        static void clean(quaternion& q);
        static float quadrance(const quaternion& q);
        static float norm(const quaternion& q);
        static quaternion normalize(const quaternion& q);
        static quaternion conjugate(const quaternion& q);
        static quaternion inverse(const quaternion& q);
        static quaternion add(const quaternion& q0, const quaternion& q1);
        static quaternion multiply(const quaternion& q, const float s);
        static quaternion multiply(const quaternion& q0, const quaternion& q1);
        static float* toOpenGLMatrix(quaternion& q);
        static matrix4D toMatrix(const quaternion& q);
        static quaternion lerp(const quaternion& q0, const quaternion& q1, float k);
        static quaternion slerp(const quaternion& q0, const quaternion& q1, float k);
        static bool isEqual(const quaternion& q0, const quaternion& q1);
        //friend quaternion operator*(const quaternion& q0, const quaternion& q1);
    
    };
}


#endif