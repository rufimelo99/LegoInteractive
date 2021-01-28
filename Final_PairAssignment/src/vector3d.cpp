#include <iostream>
#include <algorithm>
#include <cassert>
#include "vector3d.h"
#include "math.h"


using namespace Vectors;

static float eps = 1e-6;
//static double eps = std::numeric_limits<float>::epsilon();

// Constructors

vector3D::vector3D()
    : x(0.0), y(0.0), z(0.0)
{}

vector3D::vector3D(float s)
    : x(s), y(s), z(s)
{}

vector3D::vector3D(float xx, float yy, float zz)
    : x(xx), y(yy), z(zz)
{}

vector3D::vector3D(const vector3D& v)
    : x(v.x), y(v.y), z(v.z)
{}

vector3D::vector3D(const vector2D& v)
    : x(v.x), y(v.y), z(0.0)
{}

vector3D::vector3D(const vector2D& v, float s)
    : x(v.x), y(v.y), z(s)
{}

vector3D::vector3D(float s, const vector2D& v)
    : x(s), y(v.x), z(v.y)
{}

vector3D::~vector3D(){};


//Member Functions & Operator Overloads

float vector3D::getX(){
    return x;
}

float vector3D::getY(){
    return y;
}

float vector3D::getZ(){
    return z;
}

void vector3D::setX(float x1){
    x = x1;
}

void vector3D::setY(float y1){
    y = y1;
}

void vector3D::setZ(float z1){
    z = z1;
}

//bool vector3D::operator==(const vector3D& v){ 
//    return (abs(x - v.x) <= eps &&
//            abs(y - v.y) <= eps &&
//            abs(z - v.z) <= eps);
//    //return (x == v.x && y == v.y && z == v.z);
//}

bool vector3D::operator!=(const vector3D& v){
    return !(*this==v);
}

vector3D vector3D::operator=(const vector3D& v){
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

vector3D vector3D::operator+=(const vector3D& v){
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

vector3D vector3D::operator+(const vector3D& v){
    vector3D v_return(*this);
    v_return += v;
    return v_return;
}

vector3D vector3D::operator+=(float s){
    x += s;
    y += s;
    z += s;
    return *this;
}

vector3D vector3D::operator+(float s){
    vector3D v_return(*this);
    v_return += s;
    return v_return;
}

vector3D vector3D::operator-=(const vector3D& v){
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

//vector3D vector3D::operator-(const vector3D& v){
//    vector3D v_return(*this);
//    v_return -= v;
//    return v_return;
//}

vector3D vector3D::operator-=(float s){
    x -= s;
    y -= s;
    z -= s;
    return *this;
}

vector3D vector3D::operator-(float s){
    vector3D v_return(*this);
    v_return -= s;
    return v_return;
}

vector3D vector3D::operator*=(float s){
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

vector3D vector3D::operator*(float s){
    vector3D v_return(*this);
    v_return *= s;
    return v_return;
}

vector3D vector3D::operator/=(float s){
    assert(s != 0.0 && "Division by Zero");
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

vector3D vector3D::operator/(float s){
    assert(s != 0.0 && "Division by Zero");
    vector3D v_return(*this);
    v_return /= s;
    return v_return;
}

vector3D vector3D::operator++(){
    x++;
    y++;
    z++;
    return *this;
}

vector3D vector3D::operator++(int){
    vector3D v_return(*this);
    ++x;
    ++y;
    ++z;
    return v_return;
}

vector3D vector3D::operator--(){
    x--;
    y--;
    z--;
    return *this;
}

vector3D vector3D::operator--(int){
    vector3D v_return(*this);
    --x;
    --y;
    --z;
    return v_return;
}

float vector3D::operator[](int i) const
{   
    assert(i < 4 && "[] Access error: Available Indices: 0, 1, 2!");
    switch(i){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: return 0;
    }
}

//friend functions & friend operator overloads

namespace Vectors{
    std::ostream& operator<<(std::ostream& stream, const vector3D& v){ 
        stream << "[" << v.x << "," << v.y << "," << v.z << "]";
        return stream;
    }

    bool operator==(const vector3D& v1, const vector3D& v2){
        return (abs(v1.x - v2.x) < eps &&
            abs(v1.y - v2.y) < eps &&
            abs(v1.z - v2.z) < eps);
    }

    vector3D operator-(const vector3D& v1, const vector3D& v2){
        vector3D v_return(v1);
        v_return -= v2;
        return v_return;    
    }
    
	vector3D operator*(const vector3D& v, float s){
        vector3D v_return(v);
        v_return *= s;
        return v_return;
    }

	vector3D operator*(float s, const vector3D& v){
        vector3D v_return(v);
        v_return *= s;
        return v_return;
    }
	
    vector3D operator/(float s, const vector3D& v){
        assert(v.x != 0.0 && v.y != 0.0 && v.z != 0.0 && "Division by Zero");
        vector3D v_return(s / v.x, 
                          s / v.y,
                          s / v.z);
        return v_return;
    }

    vector3D operator+(float s, const vector3D& v){
        vector3D v_return(v);
        v_return += s;
        return v_return;
    }

    vector3D operator-(float s, const vector3D& v){
        vector3D v_return(s);
        v_return -= v;
        return v_return;
    }

	float dot(const vector3D& v1, const vector3D& v2){
        return float(v1.x * v2.x + 
                     v1.y * v2.y + 
                     v1.z * v2.z);
    }

	vector3D cross(const vector3D& v1, const vector3D& v2){
        return vector3D(v1.y * v2.z - v1.z * v2.y,
                        v1.z * v2.x - v1.x * v2.z,
                        v1.x * v2.y - v1.y * v2.x);
    }

	float distance(const vector3D& v1, const vector3D& v2){
        return sqrt(pow(v1.x - v2.x, 2) +
                    pow(v1.y - v2.y, 2) +
                    pow(v1.z - v2.z, 2));
    }

	float length(const vector3D& v){
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

	vector3D normalize(const vector3D& v){
        vector3D v_ret(v);
        return v_ret/ length(v_ret);
    }

	bool isEqual(const vector3D& v1, const vector3D& v2){
        vector3D v_compare(v1);
        return (v_compare == v2);
    }

	bool isNearlyEqual(const vector3D& v1, const vector3D& v2){
        return (abs(v1.x - v2.x) <= eps * std::max(1.0f, std::max(abs(v1.x), abs(v2.x))) &&
                abs(v1.y - v2.y) <= eps * std::max(1.0f, std::max(abs(v1.y), abs(v2.y))) &&
                abs(v1.z - v2.z) <= eps * std::max(1.0f, std::max(abs(v1.z), abs(v2.z))));
    }

}
 