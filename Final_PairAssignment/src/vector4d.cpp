#include <string>
#include <iostream>
#include "vector4d.h"
#include "vector3d.h"
#include "vector2d.h"
#include "math.h"
#include <cassert>

using namespace Vectors;

static float eps = 1e-6;

vector4D::vector4D()
	: x(0.0), y(0.0), z(0.0), w(0.0)
{}
vector4D::vector4D(float x, float y, float z, float w) 
	: x(x), y(y), z(z), w(w)
{}
vector4D::vector4D(float s)
	: x(s), y(s), z(s), w(s)
{}

vector4D::vector4D(const vector4D& v)
	: x(v.x), y(v.y), z(v.z), w(v.w)
{}

vector4D::vector4D(const vector3D& v)
	: x(v.x), y(v.y), z(v.z), w(0.0)
{}

vector4D::vector4D(const vector2D& v)
	: x(v.x), y(v.y), z(0.0), w(0.0)
{}

vector4D::vector4D(const vector3D& v, float s)
	: x(v.x), y(v.y), z(v.z), w(s)
{}

vector4D::vector4D(float s, const vector3D& v)
	: x(s), y(v.x), z(v.y), w(v.z)
{}

vector4D::vector4D(const vector2D& v1, const vector2D& v2)
	: x(v1.x), y(v1.y), z(v2.x), w(v2.y)
{}

vector4D::vector4D(const vector2D& v1, float s1, float s2)
	: x(v1.x), y(v1.y), z(s1), w(s2)
{}

vector4D::vector4D(float s1, const vector2D& v1, float s2)
	: x(s1), y(v1.x), z(v1.y), w(s2)
{}

vector4D::vector4D(float s1, float s2, const vector2D& v1)
	: x(s1), y(s2), z(v1.x), w(v1.y)
{}

vector4D::~vector4D(){}

float vector4D::getX() const { return x; }

float vector4D::getY() const { return y; }

float vector4D::getZ() const { return z; }

float vector4D::getW() const { return w; }

void vector4D::setX(float x) { x = x; }

void vector4D::setY(float y) { y = y; }

void vector4D::setZ(float z) { z = z; }

void vector4D::setW(float w) { w = w; }

bool vector4D::operator==(const vector4D &v) {
	return (abs(x - v.x) < eps &&
            abs(y - v.y) < eps &&
            abs(z - v.y) < eps &&
            abs(w - v.w) < eps);
}

bool vector4D::operator!=(const vector4D &v) {
	return (*this != v);
}

vector4D vector4D::operator=(const vector4D& v) {
	x = v.getX();
	y = v.getY();
	z = v.getZ();
	w = v.getW();

	return *this;
}

vector4D vector4D::operator+=(const vector4D& v) {
	x += v.getX();
	y += v.getY();
	z += v.getZ();
	w += v.getW();

	return *this;
}

vector4D vector4D::operator+(const vector4D& v) {
	vector4D v_return(*this);
    v_return += v;
    return v_return;
}

vector4D vector4D::operator-=(const vector4D& v) {
	x -= v.getX();
	y -= v.getY();
	z -= v.getZ();
	w -= v.getW();

	return *this;
}

vector4D vector4D::operator-(const vector4D& v) {
	vector4D v_return(*this);
    v_return -= v;
    return v_return;

	return *this;
}

vector4D vector4D::operator*=(float f) {
	x *= f;
	y *= f;
	z *= f;
	w *= f;

	return *this;
}

vector4D vector4D::operator*(float f) {
	vector4D v_return(*this);
    v_return *= f;
    return v_return;
}

vector4D vector4D::operator+=(float f){
	x += f;
    y += f;
    z += f;
    w += f;
    return *this;
}

vector4D vector4D::operator+(float f){
	vector4D v_return(*this);
    v_return -= f;
    return v_return;
}

vector4D vector4D::operator-=(float f){
	x -= f;
    y -= f;
    z -= f;
    w -= f;
    return *this;
}

vector4D vector4D::operator-(float f){
	vector4D v_return(*this);
    v_return -= f;
    return v_return;
}

vector4D vector4D::operator/=(float f){
	assert(f != 0.0 && "Division by Zero");
    x /= f;
    y /= f;
    z /= f;
    w /= f;
    return *this;
}

vector4D vector4D::operator/(float f){
	assert(f != 0.0 && "Division by Zero");
    vector4D v_return(*this);
    v_return /= f;
    return v_return;
}

vector4D vector4D::operator++(){
	x++;
    y++;
    z++;
    w++;
    return *this;
}

vector4D vector4D::operator++(int){
	vector4D v_return(*this);
    ++x;
    ++y;
    ++z;
    ++w;
    return v_return;
}

vector4D vector4D::operator--(){
	x--;
    y--;
    z--;
    w--;
    return *this;
}

vector4D vector4D::operator--(int){
	vector4D v_return(*this);
    ++x;
    ++y;
    ++z;
    ++w;
    return v_return;
}

float vector4D::operator[](int i) const
{	
	assert(i < 4 && "[] Access error: Available Indices: 0, 1, 2, 3!");
    switch(i){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: return 0;
    }
}

namespace Vectors{
	vector4D operator+(float f, const vector4D& v) {
		vector4D v_return(v);
        v_return += f;
        return v_return;
	}

	vector4D operator-(float f, const vector4D& v) {
		vector4D v_return(f);
        v_return -= v;
        return v_return;
	}

	vector4D operator*(float s, const vector4D& v) {
		//return vector4D(v.getX() * s, v.getY() * s, v.getZ() * s, v.getW() * s);
		vector4D v_return(v);
        v_return *= s;
        return v_return;
	}

	vector4D operator/(float f, const vector4D& v) {
		assert(v.x != 0.0 && v.y != 0.0 && v.z != 0.0 && "Division by Zero");
        vector4D v_return(f / v.x, 
                          f / v.y,
                          f / v.z,
						  f / v.w);
        return v_return;
	}

	float dot(const vector4D& v1, const vector4D& v2) {
		return v1.getX() * v2.getX() + v1.getY() * v2.getY() + v1.getZ() * v2.getZ() + v1.getW() * v2.getW();
	}
	
	float distance(const vector4D& v1, const vector4D v2){
		return sqrt(pow(v1.x - v2.x, 2) +
                    pow(v1.y - v2.y, 2) +
                    pow(v1.z - v2.z, 2) +
                    pow(v1.w - v2.w, 2));
	}

	float length(const vector4D& v){
		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
	}

	bool isEqual(const vector4D& v1, const vector4D& v2){
		vector4D v_ret(v1);
        return (v_ret == v2);
	}

	bool isNearlyEqual(const vector4D& v1, const vector4D& v2){
		return (abs(v1.x - v2.x) <= eps * std::max(1.0f, std::max(abs(v1.x), abs(v2.x))) &&
                abs(v1.y - v2.y) <= eps * std::max(1.0f, std::max(abs(v1.y), abs(v2.y))) &&
                abs(v1.z - v2.z) <= eps * std::max(1.0f, std::max(abs(v1.z), abs(v2.z))) &&
                abs(v1.w - v2.w) <= eps * std::max(1.0f, std::max(abs(v1.w), abs(v2.w))));
	}

	std::ostream& operator<<(std::ostream& stream, const vector4D& v) {
	stream << "[" << v.x << "," << v.y<< "," << v.z << "," << v.w << "]";
	return stream;
	}
}

vector4D vector4D::normalize(const vector4D& v){
	vector4D v_ret(v);
    return v_ret/ length(v_ret);
}
