#ifndef __MATRIX_2D_H__
#define __MATRIX_2D_H__

#include <string>
#include <iostream>
//#include <stdlib.h>
#include <vector>
#include "vectors.h"

using namespace Vectors;
namespace Matrices {
    
    class matrix2D {
    public:
        float values[2][2];
        float openglValues[4];

    public:
        matrix2D();
        matrix2D(const vector2D& v1, const vector2D& v2);
        matrix2D(float s);
        matrix2D(float x0, float y0, float x1, float y1);
        matrix2D(const matrix2D& m);
        ~matrix2D();

    public:
        float operator[](int i);
        bool operator==(const matrix2D& m);
        bool operator!=(const matrix2D& m);
        matrix2D operator=(const matrix2D& m);
        matrix2D operator+=(const matrix2D& m);
        matrix2D operator+(const matrix2D& m);
        matrix2D operator+=(float s);
        matrix2D operator+(float s);
        matrix2D operator-=(const matrix2D& m);
        matrix2D operator-(const matrix2D& m);
        matrix2D operator-=(float s);
        matrix2D operator-(float s);
        matrix2D operator*=(float s);
        matrix2D operator*(float s);
        matrix2D operator*=(const matrix2D& m);
        matrix2D operator*(const matrix2D& m);
        matrix2D operator/=(float s);
        matrix2D operator/(float s);
        matrix2D operator++();
        matrix2D operator++(int);
        matrix2D operator--();
        matrix2D operator--(int);
        vector2D operator*(const vector2D& v);

        friend std::ostream& operator<<(std::ostream& stream, const matrix2D& m);
        friend matrix2D operator*(float s, const matrix2D& v);
        friend matrix2D transpose(const matrix2D m);
        friend float det(const matrix2D m);
        friend matrix2D inverse(const matrix2D m);
        friend float* toOpenGL(matrix2D& m);

        static matrix2D rotationMatrix(float angle);
        static matrix2D scaleMatrix(float scale);
		static matrix2D scaleMatrix(float x, float y);
    };
}
#endif

