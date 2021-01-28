#include <cassert>
#include <iostream>
#include "matrix2d.h"
#include "math.h"

#define PI 3.14159265

using namespace Matrices;

static int dimension = 2;
static float eps = 1e-6;

matrix2D::matrix2D() {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (i == j) {
                values[i][j] = 1.0;
            }
            else {
                values[i][j] = 0.0;
            }
        }
    }
}

matrix2D::matrix2D(const vector2D& v1, const vector2D& v2){
    for (int i = 0; i < dimension; i++) {
        values[0][i] = v1[i];
        values[1][i] = v2[i];
    }
}

matrix2D::matrix2D(float s) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            values[i][j] = s;
        }
    }
}

matrix2D::matrix2D(float x0, float y0,
                   float x1, float y1) {
    values[0][0] = x0;
    values[0][1] = y0;
    values[1][0] = x1;
    values[1][1] = y1;
}

matrix2D::matrix2D(const matrix2D& m) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < 2; j++) {
            values[i][j] = m.values[i][j];
        }
    }
}

matrix2D::~matrix2D() {}

float matrix2D::operator[](int i) {
    assert(i < dimension * dimension && "Matrix Access error: Available Indices: 0 - 4!");
    int row = i / dimension;
    int col = (i - row * dimension) % dimension;
    return values[row][col];
}

bool matrix2D::operator==(const matrix2D& m) {
    bool equal = true;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            equal = abs(values[i][j] - m.values[i][j]) <= eps;
            if (!equal) {
                return false;
            }
        }
    }
    return equal;
}

bool matrix2D::operator!=(const matrix2D& m) {
    return !(*this == m);
}

matrix2D matrix2D::operator=(const matrix2D& m) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            values[i][j] = m.values[i][j];
        }
    }
    return *this;
}

matrix2D matrix2D::operator+=(const matrix2D& m) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            values[i][j] += m.values[i][j];
        }
    }
    return *this;
}

matrix2D matrix2D::operator+(const matrix2D& m) {
    matrix2D m_return(*this);
    m_return += m;
    return m_return;
}

matrix2D matrix2D::operator+=(float s) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            values[i][j] += s;
        }
    }
    return *this;
}

matrix2D matrix2D::operator+(float s) {
    matrix2D m_return(*this);
    m_return += s;
    return m_return;
}

matrix2D matrix2D::operator-=(const matrix2D& m) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            values[i][j] -= m.values[i][j];
        }
    }
    return *this;
}

matrix2D matrix2D::operator-(const matrix2D& m) {
    matrix2D m_return(*this);
    m_return -= m;
    return m_return;
}

matrix2D matrix2D::operator-=(float s) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            values[i][j] -= s;
        }
    }
    return *this;
}

matrix2D matrix2D::operator-(float s) {
    matrix2D m_return(*this);
    m_return -= s;
    return m_return;
}

matrix2D matrix2D::operator*=(float s) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            values[i][j] *= s;
        }
    }
    return *this;
}

matrix2D matrix2D::operator*(float s) {
    matrix2D m_return(*this);
    m_return *= s;
    return m_return;
}

matrix2D matrix2D::operator*=(const matrix2D& m) {
    *this = *this * m;
    return *this;
}

matrix2D matrix2D::operator*(const matrix2D& m) { 
    matrix2D m_temp(m);
    matrix2D m_mult(0.0);
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            for (int k = 0; k < dimension; k++) {
                m_mult.values[i][j] += values[i][k] * m_temp.values[k][j];
            }
        }
    }
    return m_mult;
}

matrix2D matrix2D::operator/=(float s) {
    assert(s != 0.0 && "Division by Zero");
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            values[i][j] /= s;
        }
    }
    return *this;
}

matrix2D matrix2D::operator/(float s) {
    assert(s != 0.0 && "Division by Zero");
    matrix2D m_return(*this);
    m_return /= s;
    return m_return;
}

matrix2D matrix2D::operator++() {
    (*this) += 1.0;
    return *this;
}

matrix2D matrix2D::operator++(int) {
    matrix2D m_return(*this);
    *this += 1.0;
    return m_return;
}

matrix2D matrix2D::operator--() {
    *this -= 1.0;
    return *this;
}

matrix2D matrix2D::operator--(int) {
    matrix2D m_return(*this);
    *this -= 1.0;
    return m_return;
}

vector2D matrix2D::operator*(const vector2D& v) {
    vector2D v0(values[0][0], values[0][1]);
    vector2D v1(values[1][0], values[1][1]);
    vector2D returnVec(dot(v0, v), dot(v1, v));
    return returnVec;
}

matrix2D matrix2D::rotationMatrix(float angle){
    angle *= PI /180;
    matrix2D m_rotation(cos(angle), -sin(angle),
                        sin(angle), cos(angle));
    return m_rotation;
}

matrix2D matrix2D::scaleMatrix(float scale){
    matrix2D m_scale;
    m_scale *= scale;
    return m_scale;
}

matrix2D matrix2D::scaleMatrix(float x, float y){
    matrix2D m_scale;
    m_scale.values[0][0] = x;
    m_scale.values[1][1] = y;
    return m_scale;
}

namespace Matrices {
    std::ostream& operator<<(std::ostream& stream, const matrix2D& m) {
        stream << "[";
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                if (i == dimension - 1 && j == dimension - 1) {
                    stream << m.values[i][j] << "]";
                }
                else {
                    stream << m.values[i][j] << ", ";
                }
            }
        }
        return stream;
    }

    matrix2D operator*(float s, const matrix2D& m) {
        matrix2D m_return(m);
        m_return *= s;
        return m_return;
    }

    matrix2D transpose(const matrix2D m) {
        matrix2D m_transpose(m);
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                m_transpose.values[i][j] = m.values[j][i];
            }
        }
        return m_transpose;
    }

    float det(const matrix2D m) {
        return m.values[0][0] * m.values[1][1] - m.values[1][0] * m.values[0][1];
    }

    matrix2D inverse(const matrix2D m) {
        float determinant = det(m);
        assert(determinant != 0 && "Can't invert matrix: Determinant == 0");
        float mulDet = 1 / determinant;
        float nX0 = m.values[1][1];
        float nX1 = -m.values[0][1];
        float nY0 = -m.values[1][0];
        float nY1 = m.values[0][0];

        matrix2D nMat(nX0, nX1, 
                      nY0, nY1);
        return nMat * mulDet;
    }

    float* toOpenGL(matrix2D& m){
        matrix2D m_transposed(transpose(m));
        for(int i = 0; i < dimension; i++){
            for(int j = 0; j < dimension; j++){
                m.openglValues[i * dimension + j] = m_transposed.values[i][j];
            }    
        }    
        return m.openglValues;
    }
}
