
#include <iostream>
#include <cassert>
#include "vector2d.h"
#include "math.h"

using namespace Vectors;

static double eps = 1e-6;
//static double eps = std::numeric_limits<float>::epsilon();

//constructors
vector2D::vector2D()
    : x(0.0), y(0.0)
{}

vector2D::vector2D(float s)
    : x(s), y(s)
{}

vector2D::vector2D(float xx, float yy)
    : x(xx), y(yy)
{}

vector2D::vector2D(const vector2D& v)
    : x(v.x), y(v.y)
{}

vector2D::~vector2D(){};

//Member Functions & Operator Overloads

float vector2D::getX(){
    return x;
}

float vector2D::getY(){
    return y;
}

void vector2D::setX(float x1){
    x = x1;
}

void vector2D::setY(float y1){
    y = y1;
}

bool vector2D::operator==(const vector2D& v){
    return (abs(x - v.x) <= eps &&
            abs(y - v.y) <= eps);
    //return (x == v.x && y == v.y);
}

bool vector2D::operator!=(const vector2D& v){
    return !(*this==v);
}

vector2D vector2D::operator=(const vector2D& v){
    x = v.x;
    y = v.y;
    return *this;
}

vector2D vector2D::operator+=(const vector2D& v){
    x += v.x;
    y += v.y;
    return *this;
}

vector2D vector2D::operator+(const vector2D& v){
    vector2D v_return(*this);
    v_return += v;
    return v_return;
}

vector2D vector2D::operator+=(float s){
    x += s;
    y += s;
    return *this;
}

vector2D vector2D::operator+(float s){
    vector2D v_return(*this);
    v_return += s;
    return v_return;
}

vector2D vector2D::operator-=(const vector2D& v){
    x -= v.x;
    y -= v.y;
    return *this;
}

vector2D vector2D::operator-(const vector2D& v){
    vector2D v_return(*this);
    v_return -= v;
    return v_return;
}

vector2D vector2D::operator-=(float s){
    x -= s;
    y -= s;
    return *this;
}

vector2D vector2D::operator-(float s){
    vector2D v_return(*this);
    v_return -= s;
    return v_return;
}

vector2D vector2D::operator*=(float s){
    x *= s;
    y *= s;
    return *this;
}

vector2D vector2D::operator*(float s){
    vector2D v_return(*this);
    v_return *= s;
    return v_return;
}

vector2D vector2D::operator/=(float s){
    assert(s != 0.0 && "Division by Zero");
    x /= s;
    y /= s;
    return *this;
}

vector2D vector2D::operator/(float s){
    assert(s != 0.0 && "Division by Zero");
    vector2D v_return(*this);
    v_return /= s;
    return v_return;
}

vector2D vector2D::operator++(){
    x++;
    y++;
    return *this;
}

vector2D vector2D::operator++(int){
    vector2D v_return(*this);
    ++x;
    ++y;
    return v_return;
}

vector2D vector2D::operator--(){
    x--;
    y--;
    return *this;
}

vector2D vector2D::operator--(int){
    vector2D v_return(*this);
    --x;
    --y;
    return v_return;
}

float vector2D::operator[](int i) const
{   
    assert(i < 4 && "[] Access error: Available Indices: 0, 1!");
    switch(i){
        case 0: return x;
        case 1: return y;
        default: return 0;
    }
}

//friend functions & friend operator overloads

namespace Vectors{
    std::ostream& operator<<(std::ostream& stream, const vector2D& v){ 
        stream << "[" << v.x << "," << v.y << "]";
        return stream;
    }

	vector2D operator*(const vector2D& v, float s){
        vector2D v_return(v);
        v_return *= s;
        return v_return;
    }

	vector2D operator*(float s, const vector2D& v){
        vector2D v_return(v);
        v_return *= s;
        return v_return;
    }
	
    vector2D operator/(float s, const vector2D& v){
        assert(v.x != 0.0 && v.y != 0.0 && "Division by Zero");
        vector2D v_return(s / v.x, 
                          s / v.y);
        return v_return;
    }

    vector2D operator+(float s, const vector2D& v){
        vector2D v_return(v);
        v_return += s;
        return v_return;
    }

    vector2D operator-(float s, const vector2D& v){
        vector2D v_return(s);
        v_return -= v;
        return v_return;
    }

	float dot(const vector2D& v1, const vector2D& v2){
        return float(v1.x * v2.x + 
                     v1.y * v2.y);
    }

	float distance(const vector2D& v1, const vector2D& v2){
        return sqrt(pow(v1.x - v2.x, 2) +
                    pow(v1.y - v2.y, 2));
    }

	float length(const vector2D& v){
        return sqrt(v.x * v.x + v.y * v.y);
    }

	vector2D normalize(const vector2D& v){
        vector2D v_ret(v);
        return v_ret/ length(v_ret);
    }

	bool isEqual(const vector2D& v1, const vector2D& v2){
        vector2D v_compare(v1);
        return (v_compare == v2);
    }

	bool isNearlyEqual(const vector2D& v1, const vector2D& v2){
        return (abs(v1.x - v2.x) <= eps * std::max(1.0f, std::max(abs(v1.x), abs(v2.x))) &&
                abs(v1.y - v2.y) <= eps * std::max(1.0f, std::max(abs(v1.y), abs(v2.y))));
    }

}
 