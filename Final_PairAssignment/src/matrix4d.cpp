#include "matrix4d.h"
#include "math.h"
#include <cassert>
#include <iostream>

using namespace Matrices;

#define PI 3.14159265

static int dimension = 4;
static float eps = 1e-6;

matrix4D::matrix4D(){
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

matrix4D::matrix4D(const vector4D& v1, const vector4D& v2, const vector4D& v3, const vector4D& v4){
    for(int i = 0; i < dimension; i++){
        values[0][i] = v1[i];
        values[1][i] = v2[i];
        values[2][i] = v3[i];
        values[3][i] = v4[i];
    }
}

matrix4D::matrix4D(float s){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            values[i][j] = s;
        }
    }
}

matrix4D::matrix4D(float x0, float y0, float z0, float w0,
                   float x1, float y1, float z1, float w1,
                   float x2, float y2, float z2, float w2,
                   float x3, float y3, float z3, float w3){
    values[0][0] = x0;
    values[0][1] = y0;
    values[0][2] = z0;
    values[0][3] = w0;
    values[1][0] = x1;
    values[1][1] = y1;
    values[1][2] = z1;
    values[1][3] = w1;
    values[2][0] = x2;
    values[2][1] = y2;
    values[2][2] = z2;
    values[2][3] = w2;
    values[3][0] = x3;
    values[3][1] = y3;
    values[3][2] = z3;
    values[3][3] = w3;
}

matrix4D::matrix4D(const matrix4D& m){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            values[i][j] = m.values[i][j];
        }
    }
}

matrix4D::matrix4D(const matrix3D& m){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            if(i == dimension - 1 && j == dimension - 1){
                values[i][j] = 1;
            }
            else if(i == dimension -1){
                values[i][j] = 0;
            }
            else if(j == dimension -1){
                values[i][j] = 0;
            }
            else{
                values[i][j] = m.values[i][j];
            }
        }
    }
}

matrix4D::~matrix4D(){}


//functions and operators

float matrix4D::operator[](int i){
    assert(i < dimension * dimension && "Matrix Access error: Available Indices: 0 - 15!");
    int row = i / dimension;
    int col = (i - row * dimension) % dimension;
    return values[row][col];
}

bool matrix4D::operator==(const matrix4D& m){
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

bool matrix4D::operator!=(const matrix4D& m){
    return !(*this == m);
}

matrix4D matrix4D::operator=(const matrix4D& m){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            values[i][j] = m.values[i][j];
        }
    }
    return *this;
}

matrix4D matrix4D::operator+=(const matrix4D& m){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            values[i][j] += m.values[i][j];
        }
    }
    return *this;
}

matrix4D matrix4D::operator+(const matrix4D& m){
    matrix4D m_return(*this);
    m_return += m;
    return m_return;
}

matrix4D matrix4D::operator+=(float s){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            values[i][j] += s;
        }
    }
    return *this;
}

matrix4D matrix4D::operator+(float s){
    matrix4D m_return(*this);
    m_return += s;
    return m_return;
}

matrix4D matrix4D::operator-=(const matrix4D& m){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            values[i][j] -= m.values[i][j];
        }
    }
    return *this;
}

matrix4D matrix4D::operator-(const matrix4D& m){
    matrix4D m_return(*this);
    m_return -= m;
    return m_return; 
}

matrix4D matrix4D::operator-=(float s){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            values[i][j] -= s;
        }
    }
    return *this;
}

matrix4D matrix4D::operator-(float s){
    matrix4D m_return(*this);
    m_return -= s;
    return m_return; 
}

matrix4D matrix4D::operator*=(float s){
    matrix4D m_return;
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            values[i][j] = values[i][j] * s;
        }
    }
    return *this;
}

matrix4D matrix4D::operator*(float s){
    matrix4D m_return(*this);
    m_return *= s;
    return m_return; 
}

matrix4D matrix4D::operator*=(const matrix4D& m){
    *this = *this * m;
    return *this;
}

matrix4D matrix4D::operator*(const matrix4D& m){
    matrix4D m_temp(m);
    matrix4D m_mult(0.0);
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            for (int k = 0; k < dimension; k++) {
                m_mult.values[i][j] += values[i][k] * m_temp.values[k][j];
            }
        }
    }
    return m_mult;
}


matrix4D matrix4D::operator/=(float s){
    assert(s != 0.0 && "Division by Zero");
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            values[i][j] /= s;
        }
    }
    return *this;
}

matrix4D matrix4D::operator/(float s){
    assert(s != 0.0 && "Division by Zero");
    matrix4D m_return(*this);
    m_return /= s;
    return m_return; 
}

matrix4D matrix4D::operator++(){
    (*this) += 1.0;
    return *this;
}

matrix4D matrix4D::operator++(int){
    matrix4D m_return(*this);
    *this += 1.0;
    return m_return;
}

matrix4D matrix4D::operator--(){
    *this -= 1.0;
    return *this;
}

matrix4D matrix4D::operator--(int){
    matrix4D m_return(*this);
    *this -= 1.0;
    return m_return;
}

vector4D matrix4D::operator*(const vector4D& v){
    vector4D v0(values[0][0], values[0][1], values[0][2], values[0][3]);
    vector4D v1(values[1][0], values[1][1], values[1][2], values[1][3]);
    vector4D v2(values[2][0], values[2][1], values[2][2], values[2][3]);
    vector4D v3(values[3][0], values[3][1], values[3][2], values[3][3]);
    vector4D returnVec(dot(v0, v), dot(v1, v), dot(v2, v), dot(v3, v));
    return returnVec;
}

//friend functions and operators
namespace Matrices{
    std::ostream& operator<<(std::ostream& stream, const matrix4D& m){
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

    matrix4D operator*(float s, const matrix4D& m){
        matrix4D m_return(m);
        m_return *= s;
        return m_return;
    }

    bool isEqual(const matrix4D& m1, const matrix4D& m2){
        matrix4D m1_temp(m1);
        matrix4D m2_temp(m2);
        return m1_temp == m2_temp;
    }

    matrix4D transpose(const matrix4D& m){
        matrix4D m_transpose(m);
        for(int i = 0; i < dimension; i++){
            for(int j = 0; j < dimension; j++){
                m_transpose.values[i][j] = m.values[j][i];
            }
        }
        return m_transpose;
    }

    float* toOpenGL(matrix4D& m){
        matrix4D m_transposed(transpose(m));
        for(int i = 0; i < dimension; i++){
            for(int j = 0; j < dimension; j++){
                m.openglValues[i * dimension + j] = m_transposed.values[i][j];
            }    
        }    
        return m.openglValues;
    }
}

//static functions
matrix4D matrix4D::rotationMatrix(const vector3D& axis, float angle){
    matrix3D rotation3d(matrix3D::rotationMatrix(axis, angle));
    matrix4D rotation4d(rotation3d);
    return rotation4d;
}

matrix4D matrix4D::translationMatrix(float x, float y, float z){
    matrix4D m_trans;
    m_trans.values[0][3] = x;
    m_trans.values[1][3] = y;
    m_trans.values[2][3] = z;
    return m_trans;
}

matrix4D matrix4D::translationMatrix(const vector3D& translation){
    matrix4D m_trans;
    m_trans.values[0][3] = translation.x;
    m_trans.values[1][3] = translation.y;
    m_trans.values[2][3] = translation.z;
    return m_trans;
}

matrix4D matrix4D::scaleMatrix(float scale){
    matrix3D m_scale;
    m_scale *= scale;
    return matrix4D(m_scale);
}

matrix4D matrix4D::scaleMatrix(float x, float y, float z, float w){
    matrix4D m_scale;
    m_scale.values[0][0] = x;
    m_scale.values[1][1] = y;
    m_scale.values[2][2] = z;
    m_scale.values[3][3] = w;
    return m_scale;
}

matrix4D matrix4D::scaleMatrix(const vector3D& scale){
    return scaleMatrix(scale.x, scale.y, scale.z, 1.0);
}

matrix4D matrix4D::identityMatrix(){
    matrix4D m_ident;
    return m_ident;
}

matrix4D matrix4D::createViewMatrix(const vector3D& eye, const vector3D& center, const vector3D& up){
    vector3D v(normalize(center - eye));
    vector3D s(normalize(cross(v, up)));
    vector3D u(cross(s, v));
    matrix4D mView(s.x, s.y, s.z, dot(0 - s, eye),
                   u.x, u.y, u.z, dot(0 - u, eye),
                   -v.x, -v.y, -v.z, dot(v, eye), 
                   0, 0, 0, 1);           
    return mView;
}

matrix4D matrix4D::createOrthographicMatrix(const float left, const float right, const float bottom, const float top, const float near, const float far){
    float translation1 = -(left + right) / (left - right);
    float translation2 = -(bottom + top) / (bottom - top);
    float translation3 = -(near + far) / (near - far);
    float scale1 = 2.0 / (right - left);
    float scale2 = 2.0 / (top - bottom);
    float scale3 = 2.0 / (near - far);
    matrix4D mOrtho(scale1, 0, 0, translation1,
                    0, scale2, 0, translation2,
                    0, 0, scale3, translation3,
                    0, 0, 0, 1);
    return mOrtho;
}

matrix4D matrix4D::createPerspectiveMatrix(const float fovy, const float aspect, const float nearZ, const float farZ){
    float fovy_rad = fovy * PI / 180;
    float sinTheta = sin(fovy_rad / 2.0);
    float cosTheta = cos(fovy_rad / 2.0);
    float d = cosTheta / sinTheta;
    float m00 = d / aspect;
    float m22 = (nearZ + farZ) / (nearZ - farZ);
    float m23 = float(2.0 * nearZ * farZ) / float(nearZ - farZ);
    matrix4D mPersp(m00, 0, 0, 0,
                    0, d, 0, 0,
                    0, 0, m22, m23,
                    0, 0, -1, 0);
    return mPersp;
}

matrix4D matrix4D::inverse(const matrix4D& m)
{
    double inv[16], det;
    int i;

    inv[0] = m.values[1][1] * m.values[2][2] * m.values[3][3] -
        m.values[1][1] * m.values[2][3] * m.values[3][2] -
        m.values[2][1] * m.values[1][2] * m.values[3][3] +
        m.values[2][1] * m.values[1][3] * m.values[3][2] +
        m.values[3][1] * m.values[1][2] * m.values[2][3] -
        m.values[3][1] * m.values[1][3] * m.values[2][2];

    inv[4] = -m.values[1][0] * m.values[2][2] * m.values[3][3] +
        m.values[1][0] * m.values[2][3] * m.values[3][2] +
        m.values[2][0] * m.values[1][2] * m.values[3][3] -
        m.values[2][0] * m.values[1][3] * m.values[3][2] -
        m.values[3][0] * m.values[1][2] * m.values[2][3] +
        m.values[3][0] * m.values[1][3] * m.values[2][2];

    inv[8] = m.values[1][0] * m.values[2][1] * m.values[3][3] -
        m.values[1][0] * m.values[2][3] * m.values[3][1] -
        m.values[2][0] * m.values[1][1] * m.values[3][3] +
        m.values[2][0] * m.values[1][3] * m.values[3][1] +
        m.values[3][0] * m.values[1][1] * m.values[2][3] -
        m.values[3][0] * m.values[1][3] * m.values[2][1];

    inv[12] = -m.values[1][0] * m.values[2][1] * m.values[3][2] +
        m.values[1][0] * m.values[2][2] * m.values[3][1] +
        m.values[2][0] * m.values[1][1] * m.values[3][2] -
        m.values[2][0] * m.values[1][2] * m.values[3][1] -
        m.values[3][0] * m.values[1][1] * m.values[2][2] +
        m.values[3][0] * m.values[1][2] * m.values[2][1];

    inv[1] = -m.values[0][1] * m.values[2][2] * m.values[3][3] +
        m.values[0][1] * m.values[2][3] * m.values[3][2] +
        m.values[2][1] * m.values[0][2] * m.values[3][3] -
        m.values[2][1] * m.values[0][3] * m.values[3][2] -
        m.values[3][1] * m.values[0][2] * m.values[2][3] +
        m.values[3][1] * m.values[0][3] * m.values[2][2];

    inv[5] = m.values[0][0] * m.values[2][2] * m.values[3][3] -
        m.values[0][0] * m.values[2][3] * m.values[3][2] -
        m.values[2][0] * m.values[0][2] * m.values[3][3] +
        m.values[2][0] * m.values[0][3] * m.values[3][2] +
        m.values[3][0] * m.values[0][2] * m.values[2][3] -
        m.values[3][0] * m.values[0][3] * m.values[2][2];

    inv[9] = -m.values[0][0] * m.values[2][1] * m.values[3][3] +
        m.values[0][0] * m.values[2][3] * m.values[3][1] +
        m.values[2][0] * m.values[0][1] * m.values[3][3] -
        m.values[2][0] * m.values[0][3] * m.values[3][1] -
        m.values[3][0] * m.values[0][1] * m.values[2][3] +
        m.values[3][0] * m.values[0][3] * m.values[2][1];

    inv[13] = m.values[0][0] * m.values[2][1] * m.values[3][2] -
        m.values[0][0] * m.values[2][2] * m.values[3][1] -
        m.values[2][0] * m.values[0][1] * m.values[3][2] +
        m.values[2][0] * m.values[0][2] * m.values[3][1] +
        m.values[3][0] * m.values[0][1] * m.values[2][2] -
        m.values[3][0] * m.values[0][2] * m.values[2][1];

    inv[2] = m.values[0][1] * m.values[1][2] * m.values[3][3] -
        m.values[0][1] * m.values[1][3] * m.values[3][2] -
        m.values[1][1] * m.values[0][2] * m.values[3][3] +
        m.values[1][1] * m.values[0][3] * m.values[3][2] +
        m.values[3][1] * m.values[0][2] * m.values[1][3] -
        m.values[3][1] * m.values[0][3] * m.values[1][2];

    inv[6] = -m.values[0][0] * m.values[1][2] * m.values[3][3] +
        m.values[0][0] * m.values[1][3] * m.values[3][2] +
        m.values[1][0] * m.values[0][2] * m.values[3][3] -
        m.values[1][0] * m.values[0][3] * m.values[3][2] -
        m.values[3][0] * m.values[0][2] * m.values[1][3] +
        m.values[3][0] * m.values[0][3] * m.values[1][2];

    inv[10] = m.values[0][0] * m.values[1][1] * m.values[3][3] -
        m.values[0][0] * m.values[1][3] * m.values[3][1] -
        m.values[1][0] * m.values[0][1] * m.values[3][3] +
        m.values[1][0] * m.values[0][3] * m.values[3][1] +
        m.values[3][0] * m.values[0][1] * m.values[1][3] -
        m.values[3][0] * m.values[0][3] * m.values[1][1];

    inv[14] = -m.values[0][0] * m.values[1][1] * m.values[3][2] +
        m.values[0][0] * m.values[1][2] * m.values[3][1] +
        m.values[1][0] * m.values[0][1] * m.values[3][2] -
        m.values[1][0] * m.values[0][2] * m.values[3][1] -
        m.values[3][0] * m.values[0][1] * m.values[1][2] +
        m.values[3][0] * m.values[0][2] * m.values[1][1];

    inv[3] = -m.values[0][1] * m.values[1][2] * m.values[2][3] +
        m.values[0][1] * m.values[1][3] * m.values[2][2] +
        m.values[1][1] * m.values[0][2] * m.values[2][3] -
        m.values[1][1] * m.values[0][3] * m.values[2][2] -
        m.values[2][1] * m.values[0][2] * m.values[1][3] +
        m.values[2][1] * m.values[0][3] * m.values[1][2];

    inv[7] = m.values[0][0] * m.values[1][2] * m.values[2][3] -
        m.values[0][0] * m.values[1][3] * m.values[2][2] -
        m.values[1][0] * m.values[0][2] * m.values[2][3] +
        m.values[1][0] * m.values[0][3] * m.values[2][2] +
        m.values[2][0] * m.values[0][2] * m.values[1][3] -
        m.values[2][0] * m.values[0][3] * m.values[1][2];

    inv[11] = -m.values[0][0] * m.values[1][1] * m.values[2][3] +
        m.values[0][0] * m.values[1][3] * m.values[2][1] +
        m.values[1][0] * m.values[0][1] * m.values[2][3] -
        m.values[1][0] * m.values[0][3] * m.values[2][1] -
        m.values[2][0] * m.values[0][1] * m.values[1][3] +
        m.values[2][0] * m.values[0][3] * m.values[1][1];

    inv[15] = m.values[0][0] * m.values[1][1] * m.values[2][2] -
        m.values[0][0] * m.values[1][2] * m.values[2][1] -
        m.values[1][0] * m.values[0][1] * m.values[2][2] +
        m.values[1][0] * m.values[0][2] * m.values[2][1] +
        m.values[2][0] * m.values[0][1] * m.values[1][2] -
        m.values[2][0] * m.values[0][2] * m.values[1][1];

    det = m.values[0][0] * inv[0] + m.values[0][1] * inv[4] + m.values[0][2] * inv[8] + m.values[0][3] * inv[12];

    if (det == 0) {
        std::cout << "det = 0" << std::endl;
        return false;

    }

    det = 1.0 / det;

    matrix4D invOut;
    int k = 0;
    for (i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            invOut.values[i][j] = inv[k] * det;
            k++;
        }
    }

    return invOut;
}