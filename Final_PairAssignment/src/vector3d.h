#ifndef __VECTOR_3D_H__
#define __VECTOR_3D_H__

//#include <string>
#include <iostream>
#include "vector2d.h"

namespace Vectors {

	class vector3D {
	public:
		float x;
		float y;
		float z;

	public:
		vector3D();	
		vector3D(float s);	
		vector3D(float x, float y, float z);	
		vector3D(const vector3D& v);	
		vector3D(const vector2D& v);	
		vector3D(const vector2D& v, float s);	
		vector3D(float s, const vector2D& v);	
		~vector3D();

	public:
		float getX();	
		float getY();	
		float getZ();	
		void setX(float x);	
		void setY(float y);	
		void setZ(float z);	
		//bool operator==(const vector3D& v);	
		bool operator!=(const vector3D& v);	
		vector3D operator=(const vector3D& v);	
		vector3D operator+=(const vector3D& v);	
		vector3D operator+(const vector3D& v);	
		vector3D operator+=(float s);	
		vector3D operator+(float s);	
		vector3D operator-=(const vector3D& v);	
		//vector3D operator-(const vector3D& v);	
		vector3D operator-=(float s);	
		vector3D operator-(float s);	
		vector3D operator*=(float s);	
		vector3D operator*(float s);	
		vector3D operator/=(float s);	
		vector3D operator/(float s);	
		vector3D operator++();	
		vector3D operator++(int);	
		vector3D operator--();	
		vector3D operator--(int);	
		float operator[](int i) const;

		friend std::ostream& operator<<(std::ostream& stream, const vector3D& v); 
		friend bool operator==(const vector3D& v1, const vector3D& v2);	
		friend vector3D operator-(const vector3D& v1, const vector3D& v2);	
		friend vector3D operator*(const vector3D& v, float s);	
		friend vector3D operator*(float s, const vector3D& v);	
		friend vector3D operator/(float s, const vector3D& v);	
		friend vector3D operator+(float s, const vector3D& v);	
		friend vector3D operator-(float s, const vector3D& v);	
		friend float dot(const vector3D& v1, const vector3D& v2);	
		friend vector3D cross(const vector3D& v1, const vector3D& v2);	
		friend float distance(const vector3D& v1, const vector3D& v2);	
		friend float length(const vector3D& v);	
		friend vector3D normalize(const vector3D& v);	
		friend bool isEqual(const vector3D& v1, const vector3D& v2);	
		friend bool isNearlyEqual(const vector3D& v1, const vector3D& v2);

	};

}
#endif
