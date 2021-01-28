#ifndef __MATRIX_3D_H__
#define __MATRIX_3D_H__

#include "vector3d.h"

using namespace Vectors;


namespace Matrices{
    class matrix4D;
    class matrix3D{
        public:
        float values[3][3];
        float openglValues[9];

        //constructors

        matrix3D();
        matrix3D(const vector3D& v1, const vector3D& v2, const vector3D& v3);
        matrix3D(float s);
        matrix3D(float x0, float y0, float z0,
                 float x1, float y1, float z1,
                 float x2, float y2, float z2);

        matrix3D(const matrix3D& m);
        matrix3D(const matrix4D& m);
        ~matrix3D();

        //functions & operator overloads

        float operator[](int i);
        bool operator==(const matrix3D& m);
		bool operator!=(const matrix3D& m);
        matrix3D operator=(const matrix3D& m);
		matrix3D operator+=(const matrix3D& m);
		matrix3D operator+(const matrix3D& m);
		matrix3D operator+=(float s);
		matrix3D operator+(float s);
		matrix3D operator-=(const matrix3D& m);
		matrix3D operator-(const matrix3D& m);
		matrix3D operator-=(float s);
		matrix3D operator-(float s);
		matrix3D operator*=(float s);
		matrix3D operator*(float s);
        matrix3D operator*=(const matrix3D& m);
        matrix3D operator*(const matrix3D& m);
		matrix3D operator/=(float s);
		matrix3D operator/(float s);
		matrix3D operator++();
		matrix3D operator++(int);
		matrix3D operator--();
		matrix3D operator--(int);
        vector3D operator*(const vector3D& v);

        //friend functions and operators 

        friend std::ostream& operator<<(std::ostream& stream, const matrix3D& m); 
		friend matrix3D operator*(float s, const matrix3D& v);
		friend bool isEqual(const matrix3D& v1, const matrix3D& v2);
        friend matrix3D transpose(const matrix3D& m);
        friend float det(const matrix3D& m);
        friend matrix3D inverse(const matrix3D& m);
        friend float* toOpenGL(matrix3D& m);

        //static functions

        static matrix3D dualMatrix(const vector3D& v);
        static matrix3D rotationMatrix(const vector3D& axis, float angle);
        static matrix3D scaleMatrix(float scale);
        static matrix3D scaleMatrix(float x, float y, float z);
        static matrix3D identityMatrix();
    };
}

#endif