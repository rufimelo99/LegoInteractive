#ifndef __VECTOR_2D_H__
#define __VECTOR_2D_H__

#include <string>
#include <iostream>

namespace Vectors {

	class vector2D {
	public:
		float x;
		float y;

	public:
		vector2D();

		vector2D(float s);

		vector2D(float x, float y);

		vector2D(const vector2D& v);

		~vector2D();
	
	public:
		float getX();

		float getY();

		void setX(float x);

		void setY(float y);

		bool operator==(const vector2D& v);

		bool operator!=(const vector2D& v);

		vector2D operator=(const vector2D& v);

		vector2D operator+=(const vector2D& v);

		vector2D operator+(const vector2D& v);

		vector2D operator+=(float s);

		vector2D operator+(float s);

		vector2D operator-=(const vector2D& v);

		vector2D operator-(const vector2D& v);

		vector2D operator-=(float s);

		vector2D operator-(float s);

		vector2D operator*=(float s);

		vector2D operator*(float s);

		vector2D operator/=(float s);

		vector2D operator/(float s);

		vector2D operator++();

		vector2D operator++(int);

		vector2D operator--();

		vector2D operator--(int);

		float operator[](int i) const;
		
		friend std::ostream& operator<<(std::ostream& stream, const vector2D& v); 

		friend vector2D operator*(const vector2D& v, float s);

		friend vector2D operator*(float s, const vector2D& v);

		friend vector2D operator/(float s, const vector2D& v);

		friend vector2D operator+(float s, const vector2D& v);

		friend vector2D operator-(float s, const vector2D& v);

		friend float dot(const vector2D& v1, const vector2D& v2);

		friend float distance(const vector2D& v1, const vector2D& v2);

		friend float length(const vector2D& v);

		friend vector2D normalize(const vector2D& v);

		friend bool isEqual(const vector2D& v1, const vector2D& v2);

		friend bool isNearlyEqual(const vector2D& v1, const vector2D& v2);

	};

}
#endif