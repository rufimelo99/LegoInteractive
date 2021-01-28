#include "matrix3d.h"
#include "math.h"
#include <cassert>
#include <iostream>
#include "matrix4d.h"

#define PI 3.14159265

using namespace Matrices;

static int dimension = 3;
static float eps = 1e-6;

matrix3D::matrix3D(){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            if(i == j){
                values[i][j] = 1.0;
            }
            else{
                values[i][j] = 0.0;
            }
        }
    }
}

matrix3D::matrix3D(const vector3D& v1, const vector3D& v2, const vector3D& v3){
    for(int i = 0; i < dimension; i++){
        values[0][i] = v1[i];
        values[1][i] = v2[i];
        values[2][i] = v3[i];
    }
}

matrix3D::matrix3D(float s){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            values[i][j] = s;
        }
    }
}

matrix3D::matrix3D(float x0, float y0, float z0,
                   float x1, float y1, float z1,
                   float x2, float y2, float z2){
    values[0][0] = x0;
    values[0][1] = y0;
    values[0][2] = z0;
    values[1][0] = x1;
    values[1][1] = y1;
    values[1][2] = z1;
    values[2][0] = x2;
    values[2][1] = y2;
    values[2][2] = z2;
}

matrix3D::matrix3D(const matrix3D& m){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            values[i][j] = m.values[i][j];
        }
    }
}

matrix3D::matrix3D(const matrix4D& m){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            values[i][j] = m.values[i][j];
        }
    }
}

matrix3D::~matrix3D(){}


//functions and operators

float matrix3D::operator[](int i){
    assert(i < dimension * dimension && "Matrix Access error: Available Indices: 0 - 8!");
    int row = i / dimension;
    int col = (i - row * dimension) % dimension;
    return values[row][col];
}

bool matrix3D::operator==(const matrix3D& m){
    bool equal = true;
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            equal = abs(values[i][j] - m.values[i][j]) <= eps;
            if(!equal){
                return false;
            }
        }
    }
    return equal;
}

bool matrix3D::operator!=(const matrix3D& m){
    return !(*this == m);
}

matrix3D matrix3D::operator=(const matrix3D& m){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            values[i][j] = m.values[i][j];
        }
    }
    return *this;
}

matrix3D matrix3D::operator+=(const matrix3D& m){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            values[i][j] += m.values[i][j];
        }
    }
    return *this;
}

matrix3D matrix3D::operator+(const matrix3D& m){
    matrix3D m_return(*this);
    m_return += m;
    return m_return;
}

matrix3D matrix3D::operator+=(float s){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            values[i][j] += s;
        }
    }
    return *this;
}

matrix3D matrix3D::operator+(float s){
    matrix3D m_return(*this);
    m_return += s;
    return m_return;
}

matrix3D matrix3D::operator-=(const matrix3D& m){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            values[i][j] -= m.values[i][j];
        }
    }
    return *this;
}

matrix3D matrix3D::operator-(const matrix3D& m){
    matrix3D m_return(*this);
    m_return -= m;
    return m_return; 
}

matrix3D matrix3D::operator-=(float s){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            values[i][j] -= s;
        }
    }
    return *this;
}

matrix3D matrix3D::operator-(float s){
    matrix3D m_return(*this);
    m_return -= s;
    return m_return; 
}

matrix3D matrix3D::operator*=(float s){
    matrix3D m_return;
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            values[i][j] = values[i][j] * s;
        }
    }
    return *this;
}

matrix3D matrix3D::operator*(float s){
    matrix3D m_return(*this);
    m_return *= s;
    return m_return; 
}

matrix3D matrix3D::operator*=(const matrix3D& m){
    *this = *this * m;
    return *this;
}

matrix3D matrix3D::operator*(const matrix3D& m){
    matrix3D m_temp(m);
    matrix3D m_mult(0.0);
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            for (int k = 0; k < dimension; k++) {
                m_mult.values[i][j] += values[i][k] * m_temp.values[k][j];
            }
        }
    }
    return m_mult;
}


matrix3D matrix3D::operator/=(float s){
    assert(s != 0.0 && "Division by Zero");
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            values[i][j] /= s;
        }
    }
    return *this;
}

matrix3D matrix3D::operator/(float s){
    assert(s != 0.0 && "Division by Zero");
    matrix3D m_return(*this);
    m_return /= s;
    return m_return; 
}

matrix3D matrix3D::operator++(){
    (*this) += 1.0;
    return *this;
}

matrix3D matrix3D::operator++(int){
    matrix3D m_return(*this);
    *this += 1.0;
    return m_return;
}

matrix3D matrix3D::operator--(){
    *this -= 1.0;
    return *this;
}

matrix3D matrix3D::operator--(int){
    matrix3D m_return(*this);
    *this -= 1.0;
    return m_return;
}

vector3D matrix3D::operator*(const vector3D& v){
    vector3D v0(values[0][0], values[0][1], values[0][2]);
    vector3D v1(values[1][0], values[1][1], values[1][2]);
    vector3D v2(values[2][0], values[2][1], values[2][2]);
    vector3D returnVec(dot(v0, v), dot(v1, v), dot(v2, v));
    return returnVec;
}

// static functions

matrix3D matrix3D::dualMatrix(const vector3D& v){
    matrix3D m_dual(0, -v.z, v.y,
                    v.z, 0, -v.x,
                    -v.y, v.x, 0);
    return m_dual;
}

matrix3D matrix3D::rotationMatrix(const vector3D& axis, float angle){
    matrix3D a(matrix3D::dualMatrix(normalize(axis)));
    matrix3D a_squared(a * a);
    matrix3D ident;
    angle *= PI / 180;
    matrix3D rotation3d(ident + sin(angle) * a + (1 - cos(angle)) * a_squared);
    return rotation3d;
}

matrix3D matrix3D::scaleMatrix(float scale){
    matrix3D m_scale;
    m_scale *= scale;
    return m_scale;
}

static matrix3D scaleMatrix(float x, float y, float z){
    matrix3D m_scale;
    m_scale.values[0][0] = x;
    m_scale.values[1][1] = y;
    m_scale.values[2][2] = z;
    return m_scale;
}

 matrix3D matrix3D::identityMatrix(){
     matrix3D m_ident;
     return m_ident;
 }

//friend functions and operators
namespace Matrices{
    std::ostream& operator<<(std::ostream& stream, const matrix3D& m){
        stream << "[";
        for(int i = 0; i < dimension; i++){
            for(int j = 0; j < dimension; j++){
                if(i == dimension - 1 && j == dimension - 1){
                    stream << m.values[i][j] << "]";
                }
                else{
                    stream << m.values[i][j] << ", ";
                }
            }
        }
        return stream;
    }

    matrix3D operator*(float s, const matrix3D& m){
        matrix3D m_return(m);
        m_return *= s;
        return m_return;
    }

    bool isEqual(const matrix3D& m1, const matrix3D& m2){
        matrix3D m1_temp(m1);
        matrix3D m2_temp(m2);
        return m1_temp == m2_temp;
    }

    matrix3D transpose(const matrix3D& m){
        matrix3D m_transpose(m);
        for(int i = 0; i < dimension; i++){
            for(int j = 0; j < dimension; j++){
                m_transpose.values[i][j] = m.values[j][i];
            }
        }
        return m_transpose;
    }

    float det(const matrix3D& m){
        float component1 = m.values[0][0] * ((m.values[1][1] * m.values[2][2]) - (m.values[1][2] * m.values[2][1]));
        float component2 = m.values[0][1] * ((m.values[1][0] * m.values[2][2]) - (m.values[1][2] * m.values[2][0]));
        float component3 = m.values[0][2] * ((m.values[1][0] * m.values[2][1]) - (m.values[1][1] * m.values[2][0]));
        return component1 - component2 + component3;
    }

    matrix3D inverse(const matrix3D& m){
        float determinant = det(m);
        assert(determinant != 0 && "Can't invert matrix: Determinant == 0");
        float invdet = 1 / determinant;
        float adj00 = m.values[1][1] * m.values[2][2] - m.values[1][2] * m.values[2][1];
        float adj01 = m.values[1][0] * m.values[2][2] - m.values[1][2] * m.values[2][0];
        float adj02 = m.values[1][0] * m.values[2][1] - m.values[1][1] * m.values[2][0];
        float adj10 = m.values[0][1] * m.values[2][2] - m.values[0][2] * m.values[2][1];
        float adj11 = m.values[0][0] * m.values[2][2] - m.values[0][2] * m.values[2][0];
        float adj12 = m.values[0][0] * m.values[2][1] - m.values[0][1] * m.values[2][0];
        float adj20 = m.values[0][1] * m.values[1][2] - m.values[0][2] * m.values[1][1];
        float adj21 = m.values[0][0] * m.values[1][2] - m.values[0][2] * m.values[1][0];
        float adj22 = m.values[0][0] * m.values[1][1] - m.values[0][1] * m.values[1][0];
        matrix3D m_adj(adj00, -adj01, adj02,
                       -adj10, adj11, -adj12,
                       adj20, -adj21, adj22);
        matrix3D m_transpose(transpose(m_adj));
        return m_transpose * invdet;
    }

    float* toOpenGL(matrix3D& m){
        matrix3D m_transposed(transpose(m));
        for(int i = 0; i < dimension; i++){
            for(int j = 0; j < dimension; j++){
                m.openglValues[i * dimension + j] = m_transposed.values[i][j];
            }    
        }    
        return m.openglValues;
    }

}
