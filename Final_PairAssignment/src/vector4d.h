#ifndef __VECTOR_4D_H__
#define __VECTOR_4D_H__

#include <string>
#include <iostream>
#include "vector3d.h"
#include "vector2d.h"

namespace Vectors {

	class vector4D {
	public:
		float x;
		float y;
		float z;
		float w;

	public:

		vector4D();	
		vector4D(float s);	
		vector4D(float x, float y, float z, float w);	
		vector4D(const vector4D& v);	
		vector4D(const vector3D& v);	
		vector4D(const vector2D& v);	
		vector4D(const vector3D& v, float s);	
		vector4D(float s, const vector3D& v);	
		vector4D(const vector2D& v1, const vector2D& v2);	
		vector4D(const vector2D& v1, float s1, float s2);	
		vector4D(float s1, const vector2D& v1, float s2);	
		vector4D(float s1, float s2, const vector2D& v1);	
		~vector4D();

	public:
	
		float getX () const;	
		float getY () const;	
		float getZ () const;	
		float getW () const;	
		void setX(float x);	
		void setY(float y);	
		void setZ(float z);	
		void setW(float w);	
		bool operator==(const vector4D& v);	
		bool operator!=(const vector4D& v);	
		vector4D operator=(const vector4D& v);	
		vector4D operator+=(const vector4D& v);	
		vector4D operator+(const vector4D& v);	
		vector4D operator-=(const vector4D& v);	
		vector4D operator-(const vector4D& v);	
		vector4D operator*=(float f);	
		vector4D operator*(float f);	
		vector4D operator+=(float f);	
		vector4D operator+(float f);	
		vector4D operator-=(float f);	
		vector4D operator-(float f);	
		vector4D operator/=(float f);	
		vector4D operator/(float f);	
		vector4D operator++();	
		vector4D operator++(int);	
		vector4D operator--();	
		vector4D operator--(int);

		float operator[](int i) const;	
		friend vector4D operator+(float f, const vector4D& v2);	
		friend vector4D operator-(float f, const vector4D& v2);	
		friend vector4D operator*(float s, const vector4D& v);	
		friend vector4D operator/(float f, const vector4D& v);	
		friend float dot(const vector4D& v1, const vector4D& v2);	
		friend float distance(const vector4D& v1, const vector4D& v2);	
		friend float length(const vector4D& v);	
		static vector4D normalize(const vector4D& v);	
		friend bool isEqual(const vector4D& v1, const vector4D& v2);	
		friend bool isNearlyEqual(const vector4D& v1, const vector4D& v2);	
		friend std::ostream& operator<<(std::ostream& stream, const vector4D& v);

	};

}
#endif

