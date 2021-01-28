#ifndef __MATRIX_4D_H__
#define __MATRIX_4D_H__

#include "vector3d.h"
#include "vector4d.h"
#include "matrix3d.h"

using namespace Vectors;
namespace Matrices{

    class matrix4D{
        public:
        float values[4][4];
        float openglValues[16];

        //constructors

        matrix4D();
        matrix4D(const vector4D& v1, const vector4D& v2, const vector4D& v3, const vector4D& v4);
        matrix4D(float s);
        matrix4D(float x0, float y0, float z0, float w0,
                 float x1, float y1, float z1, float w1,
                 float x2, float y2, float z2, float w2,
                 float x3, float y3, float z3, float w3);

        matrix4D(const matrix4D& m);
        matrix4D(const matrix3D& m);
        ~matrix4D();

        //functions & operator overloads

        float operator[](int i);
        bool operator==(const matrix4D& m);
		bool operator!=(const matrix4D& m);
        matrix4D operator=(const matrix4D& m);
		matrix4D operator+=(const matrix4D& m);
		matrix4D operator+(const matrix4D& m);
		matrix4D operator+=(float s);
		matrix4D operator+(float s);
		matrix4D operator-=(const matrix4D& m);
		matrix4D operator-(const matrix4D& m);
		matrix4D operator-=(float s);
		matrix4D operator-(float s);
		matrix4D operator*=(float s);
		matrix4D operator*(float s);
        matrix4D operator*=(const matrix4D& m);
        matrix4D operator*(const matrix4D& m);
		matrix4D operator/=(float s);
		matrix4D operator/(float s);
		matrix4D operator++();
		matrix4D operator++(int);
		matrix4D operator--();
		matrix4D operator--(int);
        vector4D operator*(const vector4D& v);

        //friend functions and operators 

        friend std::ostream& operator<<(std::ostream& stream, const matrix4D& m); 
		friend matrix4D operator*(float s, const matrix4D& v);
		friend bool isEqual(const matrix4D& v1, const matrix4D& v2);
        friend matrix4D transpose(const matrix4D& m);
        friend float* toOpenGL(matrix4D& m);

        //static functions

        static matrix4D rotationMatrix(const vector3D& axis, float angle);
        static matrix4D translationMatrix(float x, float y, float z);
        static matrix4D translationMatrix(const vector3D& translation);
        static matrix4D scaleMatrix(float scale);
        static matrix4D scaleMatrix(float x, float y, float z, float w);
        static matrix4D scaleMatrix(const vector3D& scale);
        static matrix4D identityMatrix();

        static matrix4D createViewMatrix(const vector3D& eye, const vector3D& center, const vector3D& up);
        static matrix4D createOrthographicMatrix(const float left, const float right, const float bottom, const float top, const float near, const float far);
        static matrix4D createPerspectiveMatrix(const float fovy, const float aspect, const float nearZ, const float farZ);
        static matrix4D inverse(const matrix4D& m);
    };
}

#endif